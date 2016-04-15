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
#include "comm/usb.h"
#include "comm/ble.h"
#include "driver/charger.h"
#include "driver/ameter.h"
#include "driver/pmeter.h"
#include "motion/wheelsensor.h"

#define MAX_SLEEP 60			// if there is no action for 60s go to deep sleep
#define MAX_HIBERNATION (60*60)	// after 1 h (60 * 60 = 3600) standby go for hibernation

// Global Variables
// ***************
volatile bool sleep_wakeup = FALSE;
volatile bool standby = FALSE;
volatile bool low_energy = FALSE;
volatile uint8_t waitTimeout = 0;

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
 *      Called by the Wakeup-Timer interrupt
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
 *      Waits the specified time in tens of ms. CPU is in wait mode
 *  @param
 *      time    Wait time in 10 ms
 */
/* ===================================================================*/
void wait_10ms(int time) {
    int i;
    
    Wakeup_Enable(WakeupPtr); // start the timer for 10 ms
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
 *      Called every 20 ms by main loop.
 *      Interrupts from BTN1 (Mode Button), ReedInt, and RTC1 can wake up the CPU.
 *      Wakeup Interrupt Controller (WIC) is used to wake from interruptions
 *      
 */
/* ===================================================================*/
void powermgr_DeepSleep() {
	if (sleep_wakeup) {
		// wake up by mode button or wheel turn -> reset timeouts
		sleep_timeout = 0;
		sleep_wakeup = FALSE;
		hibernation_timeout = 0;
		rotating = FALSE;

	} else {
		if (sleep_timeout >= MAX_SLEEP) {
			// -> go to sleep (again)
			pmeter_setStandby();
			disable_BatMeasure();
			USBpoll_Disable(usb_TimerPtr); // no interruption from USB
			rotating = FALSE;
			standby = TRUE;
			// ble_reset(); 
			Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_1);
			while (! sleep_wakeup) {
				Cpu_VLPModeEnable();
				Cpu_SetOperationMode(DOM_SLEEP, NULL, NULL);
				// enter deep sleep mode -> exit by any enabled interrupt
				// wake up by RTC every second

#ifdef ACCELEROMETER
				if (hibernation_timeout == MAX_HIBERNATION) {
#ifdef HALL_SENSOR
					HallVCC_ClrVal(NULL); // switch off Hall sensor
#endif
					Cpu_VLPModeDisable();
					Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_0);
					USBpoll_Enable(usb_TimerPtr);
					ble_lowPower();
					wait_10ms(200);
					BL600_Disable();
					ameter_getOrientation(); // Clear ameter orientation interrupt
					AccInt_Enable(AccIntPtr);
					USBpoll_Disable(usb_TimerPtr); // no interruption from USB
					hibernation_timeout++; // only for the first time

					Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_1);
				}
#endif
			}
			// after wakeup
			Cpu_VLPModeDisable();
			Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_0);


			pmeter_setActive();
			enable_BatMeasure();
			USBpoll_Enable(usb_TimerPtr);
#ifdef ACCELEROMETER
			if (hibernation_timeout >= MAX_HIBERNATION) {
				// wake up BLE
#ifdef HALL_SENSOR
				HallVCC_SetVal(NULL); // switch on Hall sensor
#endif
				BL600_Enable();
				ble_Init();
				AccInt_Disable(AccIntPtr);
			}
#endif
			sleep_wakeup = FALSE;
			sleep_timeout = 0;
			hibernation_timeout = 0;
			standby = FALSE;
		}

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


