/**
 *  @brief
 *      Calculates time related informations for the cyclocomputer.
 *      
 *      trip time
 *      current time
 *      stopwatch
 *      
 *  @file
 *      watch.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

/**
 **  @defgroup watch_module Watch module
 **  @{
 */         
/* MODULE Watch */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

// PE include files
// ****************
#include "PE_Types.h"
#include "RTC1.h"
#include "ChargeStat.h"
#include "BLlink.h"

// application include files
// *************************
#include "definitions.h"
#include "watch.h"
#include "usb.h"
#include "wheelsensor.h"
#include "display.h"
#include "cyclocomputer.h"
#include "pmeter.h"
#include "powermgr.h"
#include "cli.h"
#include "charger.h"
#include "ble.h"


// Global Variables
// ****************
double tripTime = 0.0;		/**< trip time [s] */
double currTime = 0.0;		/**< current time [s] since 1.1.2000 ? */
double chronoTime = 0.0;	/**< stop (chrono) watch time [s] */
double totalTime = 0.0;		/**< total time [s] */
double upTime = 0.0;		/**< up time [s] */
LDD_RTC_TTime watchTime = {	0, 0, 19, 5, 27, 3, 2015 };	    /**< watch time */

bool stopWatchRunning;

char timeStr[20];		/**< HH:MM:SS */
char dateStr[20];      	/**< DD:MM:YYYY */

LDD_TDeviceData* watchPtr;


// Local Variables
// ***************

static bool watchBlocked = TRUE;


/*
 ** ===================================================================
 **  Method      :  watch_Init
 */
/**
 *  @brief
 *  	Initialises the real time counter
 */
/* ===================================================================*/
void watch_Init() {
    watchPtr = RTC1_Init(NULL, FALSE);
    RTC1_SetTime(watchPtr, &watchTime);
    watchBlocked = FALSE;
}


/*
 ** ===================================================================
 **  Method      :  calc_Altitude
 */
/**
 *  @brief
 *  	calculates altitude, trip altitude, maximum altitude, incline, and
 *  	temperature.
 *  	Called every second by watch.
 */
/* ===================================================================*/
static void calc_Altitude() {
	static bool firstTime = TRUE;
	static double lastAltitude = 0.0;
	static double lastDistance = 0.0;
	static double altArray[4] = {0.0, 0.0, 0.0, 0.0};	/* for averaging the altitude */
	static uint8_t altIndex = 0;

	if (pmeter_acquireData() > 0) {
		// valid data
		if (firstTime) {
			firstTime = FALSE;
			currAltitude = pmeter_getAltitude();
			lastAltitude = currAltitude;
			// fill the buffer
			altArray[0] = currAltitude;
			altArray[1] = currAltitude;
			altArray[2] = currAltitude;
			altArray[3] = currAltitude;
		} else {
			altArray[altIndex++] = pmeter_getAltitude();
			if (altIndex >= 4) {
				altIndex = 0;
			}
			currAltitude = (altArray[0] + altArray[1] + altArray[2] + altArray[3]) / 4.0  ; // averaging altitude

			if ((currAltitude - lastAltitude) > 2.0 ) {
				// elevation gain
				if (tripMode == TRIP_STARTED) {
					tripElevationGain = tripElevationGain + currAltitude - lastAltitude;
				}
				totalElevationGain = totalElevationGain + currAltitude - lastAltitude;
				if (totalDistance - lastDistance >= 0) {
					incline = 100 * (currAltitude - lastAltitude) / (totalDistance - lastDistance);
				}
				lastDistance = totalDistance;
				lastAltitude = currAltitude;
			} else if ((lastAltitude - currAltitude) > 2.0 ) {
				// elevation loss
				if (tripMode == TRIP_STARTED) {
					tripElevationLoss = tripElevationLoss + currAltitude - lastAltitude;
				}
				totalElevationLoss = totalElevationLoss + currAltitude - lastAltitude;
				if (totalDistance - lastDistance >= 0) {
					incline = 100 * (currAltitude - lastAltitude) / (totalDistance - lastDistance);
				}
				lastDistance = totalDistance;
				lastAltitude = currAltitude;
			}

			if (totalDistance - lastDistance > 200.0) {
				// incline < 1 %
				incline = 0.0;
			}

			if (currAltitude > maxAltitude) {
				maxAltitude = currAltitude;
			}
		}

		// temperature
		temperature = pmeter_getTemperature();
	}

}


/*
 ** ===================================================================
 **  Method      :  watch_Synch
 */
/**
 *  @brief
 *  	Interrupt from RTC1 (every second).
 */
/* ===================================================================*/
void watch_Synch() {
	char str[20];
	
	if (rotationTime < 0) {
		currSpeed = 0.0;
	}
	
	upTime = upTime + 1.0;
	if (chronoMode == TRIP_STARTED) {
		chronoTime = chronoTime + 1.0;
	}
	
	if (tripMode == TRIP_STARTED) {
		if (trip_timeout == TRIP_TIMEOUT) {
			tripMode = TRIP_PAUSED;
		} else {
			trip_timeout++;
			tripTime = tripTime + 1.0;
			totalTime = totalTime + 1.0;
			// altitude, trip elevation gain, maximum altitude, and temperature
			calc_Altitude();
		}
	}

	if ( (! rotating) && (operating_mode == NORMAL) ) {
		// not rotating and in normal mode
		// battery charging and bluetooth link established is showed 
		charger_show_state();
		ble_show_state();
		usb_show_state();
		write_ledColumn(TOPSIDE);
		wait_ledColumn();
		
		clear_leds(BOTTOMSIDE);
		write_ledColumn(BOTTOMSIDE);
		wait_ledColumn();
	}
	
	if (! standby) {
		if (!watchBlocked) {
			RTC1_GetTime(watchPtr, &watchTime);
		}

		itoa2(watchTime.Hour, timeStr);
		strcat(timeStr, ":");
		itoa2(watchTime.Minute, str);
		strcat(timeStr, str);
		strcat(timeStr, ":");
		itoa2(watchTime.Second, str);
		strcat(timeStr, str);

		itoa2(watchTime.Day, dateStr);
		strcat(dateStr, ".");
		itoa2(watchTime.Month, str);
		strcat(dateStr, str);
		strcat(dateStr, ".");
		ltoa(watchTime.Year, str);
		strcat(dateStr, str);

		// battery voltage
		start_BatMeasure();

		if (batteryVoltage < 3.0) {
			// low_energy = TRUE;
		}

	}
}

/**
 ** @}
 */

