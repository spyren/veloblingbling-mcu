/**
 *  @brief
 *  	A Li-Polymer Charge Management Controller MCP73832T-2ACI/OT is used to 
 *  	charge the battery.
 *  	
 *  	Voltage divider 10 k / 2.2 k
 *  	Vref = 1.195 V
 *  	VAdisable	Input/Output Pin, Input: no voltage divider; Output 0: voltage divider enable
 *  	ChargeStat	Input Pin 0: charging
 *  	ChargeInh	Input/Output Pin, Input: charge enable; Output 1: charge disable
 *  	
 *  	3.0 V minimum battery voltage
 *  	3.7 V nominal battery voltage
 *  	4.2 V maximum charge voltage
 *      
 *  @file
 *      charger.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-10-11
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
 **  @defgroup display_module charger
 **  @{
 */         
/* MODULE display */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

// PE include files
// ****************
#include "PE_Types.h"
#include "ADC.h"
#include "VAdisable.h"
#include "ChargeStat.h"
#include "USBpoll.h"

// application include files
// *************************
#include "definitions.h"
#include "charger.h"
#include "visual/led.h"
#include "powermgr.h"
#include "comm/usb.h"


#define VOLTAGE_DIVIDER		(12.2/2.2)
#define V_REF 				1.195								// data sheet 1.195 V, measured 1.2 V
#define ADC_RESOLUTION		VOLTAGE_DIVIDER * (V_REF / 65535)


// Global Variables
// ****************
volatile double batteryVoltage;

// Local Variables
// ***************

/*
 ** ===================================================================
 **  Method      :  charger_Init
 */
/**
 *  @brief
 *      Inits the battery measurement
 *  
 */
/* ===================================================================*/
void charger_Init() {
	// ChargeInh_Init();
	enable_BatMeasure();
}


/*
 ** ===================================================================
 **  Method      :  enable_BatMeasure
 */
/**
 *  @brief
 *      Enables the battery measurement  
 */
/* ===================================================================*/
void enable_BatMeasure() {
	VAdisable_SetDir(NULL, TRUE);	// enable the voltage divider 
	ADC_Enable();
}


/*
 ** ===================================================================
 **  Method      :  disable_BatMeasure
 */
/**
 *  @brief
 *      Disables the battery measurement (e.g. for power down mode)  
 */
/* ===================================================================*/
void disable_BatMeasure() {
	VAdisable_SetDir(NULL, FALSE);	// disable the voltage divider 
	ADC_Disable();
}


/*
 ** ===================================================================
 **  Method      :  start_BatMeasure
 */
/**
 *  @brief
 *      Starts the battery measurement
 *  
 *  It is called regularly from a timer interrupt (every 1 s).
 *  After the ADC conversion get_BatMeasure will be called by interrupt. 
 *  
 */
/* ===================================================================*/
void start_BatMeasure() {
	ADC_Measure(FALSE);	
}


/*
 ** ===================================================================
 **  Method      :  get_BatMeasure
 */
/**
 *  @brief
 *      Gets the value from the ADC and calculates the voltage
 *  
 *  It is called by the ADC interrupt
 *  
 */
/* ===================================================================*/
void get_BatMeasure() {
	word value;
	
	ADC_GetValue16(&value);
	batteryVoltage = value * ADC_RESOLUTION;
}


/*
 ** ===================================================================
 **  Method      :  clearChargerLEDs
 */
/**
 *  @brief
 *      Clears the charger LEDs (1..14)
 */
/* ===================================================================*/
static void clearChargerLEDs() {
	LED_nrT LED;

	for (LED = LED1; LED < LED14; LED++) {
		set_led(TOPSIDE, LED, BLACK);
	}
	LEDred_SetVal();
	LEDgreen_SetVal();
}

/*
 ** ===================================================================
 **  Method      :  charger_show_state
 */
/**
 *  @brief
 *      Shows the battery state.
 *      Called every second by watch_synch.
 */
/* ===================================================================*/
void charger_show_state() {
	static float lastBatteryVoltage = 0.0;
	static bool lastCharge = FALSE;

	static LED_nrT LED = LED1;
	
#ifdef USB_VOLTAGE_DETECTION
	if (UsbSupply_GetVal()) {
		sleep_wakeup = TRUE;
		// USBpoll_Enable(usb_TimerPtr);
	} else {
		// USBpoll_Disable(usb_TimerPtr);
	}
#endif

	if (ChargeStat_GetVal(NULL)) {
		// not charging
		lastCharge = FALSE;
		clearChargerLEDs();
#ifdef USB_VOLTAGE_DETECTION
		if (UsbSupply_GetVal()) {
			set_led(TOPSIDE, LED13, GREEN);
		}
#endif
		lastBatteryVoltage = batteryVoltage;
	} else {
		if ( (fabs (batteryVoltage - lastBatteryVoltage) > 0.05) || !lastCharge) {
			// battery voltage has been changed
			lastCharge = TRUE;
			lastBatteryVoltage = batteryVoltage;
			if (lastBatteryVoltage < 2.9) {
				lastBatteryVoltage = 2.9;
			} else if (lastBatteryVoltage > 4.2) {
				lastBatteryVoltage = 4.2;
			}
			LED = (lastBatteryVoltage - 2.9) / 0.1;
			clearChargerLEDs();
		}
		if (LED > LED11) {
			set_led(TOPSIDE, LED, GREEN);
			LEDgreen_ClrVal();
		} else {
			set_led(TOPSIDE, LED, RED);
			LEDred_ClrVal();
		}
	}
}


/**
 ** @}
 */
