/**
 *  @brief
 *      Power manager (e.g. interrupt instead of busy wait)
 *      
 *  @file
 *      powermgr.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2013-12-04
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 *  @copyright
 *      Peter Schmid, Switzerland
 *
 *      This file is part of "Velo Bling-Bling" main MCU firmware.
 *
 *		"Velo Bling-Bling" firmware is free software: you can redistribute it
 *		and/or modify it under the terms of the GNU General Public License as
 *		published by the Free Software Foundation, either version 3 of the
 *		License, or (at your option) any later version.
 *
 *		"Velo Bling-Bling" is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License along
 *		with "Velo Bling-Bling". If not, see <http://www.gnu.org/licenses/>.
 */

/**
 **  @defgroup powermgr_module Power manager
 **  @{
 */         
/* MODULE powermgr */

// system include files
// ********************

// PE include files
// ****************
#include "Cpu.h"
#include "Wakeup.h"
#include "USBpoll.h"
#include "Tick.h"
#include "AccInt.h"

// application include files
// *************************
#include "definitions.h"
#include "powermgr.h"
#include "visual/led.h"
#include "visual/oled.h"
#include "comm/usb.h"
#include "comm/ble.h"
#include "driver/charger.h"
#include "driver/ameter.h"
#include "driver/pmeter.h"
#include "motion/wheelsensor.h"

#define MAX_SLEEP 60				// if there is no action for 60 s go to deep sleep
#define MAX_HIBERNATION (15*60)		// after 15 Minutes standby go for hibernation
//#define MAX_HIBERNATION (2*60)	// after 2 Minutes standby go for hibernation (only for tests)

// Global Variables
// ***************
volatile bool sleep_wakeup = FALSE;
volatile bool standby = FALSE;
volatile energy_modeT energy_mode = ENERGY_STANDARD;
volatile uint8_t waitTimeout = 0;
bool slowHall_Present = FALSE;			/**< a slow Hall sensor is present  */

// Local Variables
// ***************
static volatile int sleep_timeout = 0;
static volatile int hibernation_timeout = 0;
static volatile bool wait_timeout = FALSE;
static LDD_TDeviceData* WakeupPtr;
static LDD_TDeviceData* TickPtr;


/*
 ** ===================================================================
 **  Method      :  powermgr_Init
 */
/**
 *  @brief
 *  	Initialises the wait counter
 */
/* ===================================================================*/
void powermgr_Init() {
	WakeupPtr = Wakeup_Init(NULL);
	TickPtr   = Tick_Init(NULL);
}


/*
 ** ===================================================================
 **  Method      :  wait_int
 */
/**
 *  @brief
 *      Called by the Wakeup-Timer interrupt every 10 ms
 *      
 *  This interrupt service routine releases the CPU wait state in 
 *  wait_ms
 */
/* ===================================================================*/
void wait_int() {
	wait_timeout = TRUE;
}

/*
 ** ===================================================================
 **  Method      :  wait_10ms
 */
/**
 *  @brief
 *      Waits the specified time in tens of ms. CPU is in wait mode.
 *  @param
 *      time    Wait time in 10 ms
 */
/* ===================================================================*/
void wait_10ms(int time) {
    int i;
    
    Wakeup_Enable(WakeupPtr); // start the 10 ms timer
    for (i=0; i<time; i++) {
        while(1) {
        	//Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_3);
            Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
            if (wait_timeout) {
                wait_timeout = FALSE;
                break;
            }
        }
    }
    Wakeup_Disable(WakeupPtr); // stop the timer
	//Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_0);
}


/*
 ** ===================================================================
 **  Method      :  powermgr_DeepSleep
 */
/**
 *  @brief
 *      Stops the CPU if there is no wheel turn or no Mode button event for more than MAX_SLEEP s. 
 *      CPU goes into Stop mode.
 *      
 *      sleep_timeout and hibernation_timeout are incremented every second by powermgr_Second()
 *
 *      Called every 20 ms by main loop, except for the operating_mode INTERACTIVE_USB.
 *
 *      Following interrupts can wake up the CPU:
 *        - BTN1 (Mode Button)
 *        - ReedInt (fast and slow Hall sensor, wheelsensor)
 *        - RTC1 (real time clock, watch)
 *        - UART0 (BLE Module, ble)
 *        - AccInt (movement detection by accelerometer, ameter)
 *      Wakeup Interrupt Controller (WIC) is used to wake from interruptions
 *      
 */
/* ===================================================================*/
void powermgr_DeepSleep() {
	if (sleep_wakeup | energy_mode == ENERGY_ALWAYS_ON) {
		// reset timeouts by events:
		// mode button, UART (BLE) or wheel turn
		sleep_timeout = 0;
		sleep_wakeup = FALSE;
		hibernation_timeout = 0;
	}

	// check for sleep
	if (sleep_timeout >= MAX_SLEEP) {
		// -> go to sleep (again)
		pmeter_setStandby();			// pmeter standby to save energy
		disable_BatMeasure();			// no ADC to save energy
		USBpoll_Disable(usb_TimerPtr); 	// no interruption from USB
		rotating = FALSE;
		standby = TRUE;
		oled_setState(OLED_STANDBY);
		// ble_reset();
		Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_1);
		while (! sleep_wakeup) {
			Cpu_VLPModeEnable();
			Cpu_SetOperationMode(DOM_SLEEP, NULL, NULL);
			// enter deep sleep mode -> exit by any enabled interrupt
			// wake up by RTC every second

			if (hibernation_timeout == MAX_HIBERNATION) {
				// got to hibernation
				if (slowHall_Present || ameter_Present) {
					// switch off fast Hall sensor to save energy
					HallVCC_ClrVal(NULL);
				}

				// for configuration we need fast clock
				Cpu_VLPModeDisable();
				Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_0);

				if (ble_Present) {
					// disable BLE to save energy
					ble_lowPower();
					wait_10ms(200);
					BL600_Disable();
				}
				if (ameter_Present) {
					// enable wake up for movement detection (ameter)
					ameter_getOrientation(); // Clear ameter orientation interrupt
					AccInt_Enable(AccIntPtr);
				}
				oled_setState(OLED_OFF);

				hibernation_timeout++; // only for the first time

				Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_1);
			}
		}

		// after wake up
		Cpu_VLPModeDisable();
		Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_0);

		pmeter_setActive();
		enable_BatMeasure();
		USBpoll_Enable(usb_TimerPtr);
		oled_setState(OLED_ON);

		if (hibernation_timeout >= MAX_HIBERNATION) {
			// wake up from hibernation
			if (slowHall_Present || ameter_Present) {
				// switch on fast Hall sensor
				HallVCC_SetVal(NULL); // switch on Hall sensor
			}

			if (ble_Present) {
				// wake up BLE
				BL600_Enable();
				ble_Init();
			}

			if (ameter_Present) {
				// disable interrupts from movement detection (ameter)
				AccInt_Disable(AccIntPtr);
			}
		}

		sleep_wakeup = FALSE;
		sleep_timeout = 0;
		hibernation_timeout = 0;
		standby = FALSE;
	}

}



/*
 ** ===================================================================
 **  Method      :  powermgr_Second
 */
/**
 *  @brief
 *      Clocks the seconds for the sleep timeout.
 *      Clocks the seconds for the hibernation timeout.
 *      
 *      Called every second by RTC (Events.c).
 *      
 */
/* ===================================================================*/
void powermgr_Second() {


	if (sleep_timeout < MAX_SLEEP) {
		sleep_timeout++;
	}

	if (hibernation_timeout < MAX_HIBERNATION) {
		hibernation_timeout++;
	}
}


/*
** ===================================================================
**  Method      :  busywait_timeout
*/
/**
 *  @brief
 *  	Timeout for busy wait.
 *  	It is called regularly from the tick timer interrupt (20 ms)
 *  	
 */
/* ===================================================================*/
void busywait_timeout() {
	if (waitTimeout > 0) {
		waitTimeout--;
	}
}


/**
 ** @}
 */


