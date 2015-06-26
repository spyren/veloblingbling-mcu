/**
 *  @brief
 *  	Displays a pattern all around the wheel except there is
 *  	a window (see module display).
 *  	
 *  	After every turn the pattern is moved by n (blingStep) pixels (Western stage coach effect).
 *      
 *  @file
 *      bling.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-28
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

/**
 **  @defgroup bling_module Bling module
 **  @{
 */         
/* MODULE Bling */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

// PE include files
// ****************
#include "PE_Types.h"
//#include "BlingTimer.h"
#include "RotTimer.h"

// application include files
// *************************
#include "definitions.h"
#include "comm/usb.h"
#include "hmi/mode.h"
#include "wheelsensor.h"
#include "visual/display.h"
#include "visual/led.h"


#define TIMER_TICK (1.0/375000.0)	/* counter frequency is 375 kHz -> tick 2.667 us */ 


// Global Variables
// ****************
// double blingIntervall;
//volatile uint8_t blingLength;
volatile bool blingOn[BOTTOMSIDE+1] = {FALSE, FALSE};

// Local Variables
// ***************
static int16_t blingPosition[BOTTOMSIDE+1] = {0, 0};
static int16_t blingOffset[BOTTOMSIDE+1] = {0, 0};
static int16_t blingStep = -4;

// static LDD_TDeviceData* BlingTimerPtr;
uint16_t periodTicks;


/*
 ** ===================================================================
 **  Method      :  bling_Init
 */
/**
 *  @brief
 *  	Initialises the counters
 */
/* ===================================================================*/
void bling_Init() {
	// BlingTimerPtr = BlingTimer_Init(NULL);
}


/*
** ===================================================================
**  Method      :  bling_StartTimer
*/
/**
 *  @brief
 *  	Starts the BlingTimer (Channel 1 RotTimer/FTM0).
 *  	Called after a valid wheel synch.
 */
/* ===================================================================*/
void bling_StartTimer() {
	if (! blingOn[TOPSIDE] && ! blingOn[BOTTOMSIDE]) {
		// no bling
		return;
	}
	
	/* start timer for first column */
	// calculate time for a column
	double periodTicksD = rotationTime * (WINDOW_LENGTH / (360.0 * MAX_COLUMN)) / TIMER_TICK;
	periodTicks = periodTicksD;
	uint16_t periodOffset = RotTimer_GetCounterValue(RotTimerPtr) + periodTicks;
	
	RotTimer_SetOffsetTicks(RotTimerPtr, BLING_TIMER_CHANNEL, periodOffset);
	
	// calculate blingPosition & blingOffset for both surfaces
    // ahead or with lag
	surfaceT sur;
	for (sur=TOPSIDE; sur <= BOTTOMSIDE; sur++) {
		blingOffset[sur] = blingOffset[sur] + blingStep;
		if (blingOffset[sur] > display[sur][BLING].length) {
			blingOffset[sur] = blingOffset[sur] - display[sur][BLING].length;
		} else if (blingOffset[sur] < 0) {
			blingOffset[sur] = display[sur][BLING].length + blingOffset[sur];
		}

		if (right) {
			blingPosition[sur] = 0 + blingOffset[sur];
		} else {
			blingPosition[sur] = display[sur][BLING].length - 1 - blingOffset[sur];
		}
	}
}


/*
** ===================================================================
**  Method      :  bling_StopTimer
*/
/**
 *  @brief
 *  	Bling no longer used, stop timer and clear LEDs 
 */
/* ===================================================================*/
void bling_StopTimer() {
	// bling no longer used
	// BlingTimer_Disable(BlingTimerPtr);
	RotTimer_SetOffsetTicks(RotTimerPtr, BLING_TIMER_CHANNEL, 0xffff);
    if (right) {
    	blingPosition[TOPSIDE] = 0;
    	blingPosition[BOTTOMSIDE] = 0;
    } else {
    	blingPosition[TOPSIDE] = display[TOPSIDE][BLING].length - 1;
    	blingPosition[BOTTOMSIDE] = display[BOTTOMSIDE][BLING].length - 1;
    }
	clear_leds(TOPSIDE);
	clear_leds(BOTTOMSIDE);
}


/*
** ===================================================================
**  Method      :  bling_StartColumn
*/
/**
 *  @brief
 *  	Interrupt from BlingTimer (Channel 1 RotTimer/FTM0), reset channel offset
 */
/* ===================================================================*/
void bling_StartColumn() {
	
	// channel offset
	uint16_t periodOffset = rotTimerCh1 + periodTicks;
	RotTimer_SetOffsetTicks(RotTimerPtr, BLING_TIMER_CHANNEL, periodOffset);

	surfaceT sur;
	for (sur=TOPSIDE; sur <= BOTTOMSIDE; sur++) {
		if (blingOn[sur] && enable_bling[sur]) {
			display_blingColumn(sur, blingPosition[sur]);
		}
		if (blingOn[sur] && enable_bling[sur]) {
			display_blingColumn(sur, blingPosition[sur]);
		}

		if (right) {
			if (++blingPosition[sur] >= display[sur][BLING].length) {
				blingPosition[sur] = 0;
			}
		} else {
			if (--blingPosition[sur] < 0) {
				blingPosition[sur] = display[sur][BLING].length - 1;
			}
		}
	}
}


/**
 ** @}
 */


