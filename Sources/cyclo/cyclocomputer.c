/**
 *  @brief
 *      calculates and displays trip information, similar to the instruments in the dashboard of a car.
 *      
 *      current speed
 *      maximum speed
 *      average speed
 *      trip distance
 *      total distance
 *      altitude
 *      trip altitude
 *      total altitude
 *      maximum altitude
 *      incline
 *      temperature
 *      pedaling cadence
 *      
 *  @file
 *      cyclocomputer.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
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
 **  @defgroup cyclocomputer_module Cyclocomputer module
 **  @{
 */         
/* MODULE Cyclocomputer */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

// PE include files
// ****************
#include "PE_Types.h"

// application include files
// *************************
#include "definitions.h"
#include "cyclocomputer.h"
#include "watch.h"
#include "comm/usb.h"
#include "comm/ble.h"
#include "motion/wheelsensor.h"

// Global Variables
// ****************
double currSpeed = 0.0; 		/**< current speed [m/s] */
double maxSpeed = 0.0;			/**< maximum speed (trip) [m/s] */
double avgSpeed = 0.0;			/**< average speed (trip) [m/s] */
double tripDistance = 0.0;		/**< trip distance [m] */
double totalDistance = 0.0;		/**< total distance [m] */
double currAltitude = 0.0;		/**< altitude [m] */
double tripElevationGain = 0.0;	/**< trip elevation loss [m] */
double totalElevationGain = 0.0;/**< total elevation gain [m] */
double tripElevationLoss = 0.0;	/**< trip elevation loss [m] */
double totalElevationLoss = 0.0;/**< total elevation loss [m] */
double maxAltitude = 0.0; 		/**< maximum altitude [m] */
double incline = 0.0;			/**< incline [m] */
double temperature = 20.0;		/**< [°C] degrees centigrade */
double cadence = 0.0;			/**< cadence (not implemented yet) [s^-1] */
double altimeterOffset = 0.0;	/**< altimeter offset [m] */

uint32_t wheelRevo = 0;			/**< cumulative wheel revolutions (unitless) */
uint16_t wheelTime = 0;			/**< last wheel event time (1/1024 s) */

Trip_ModeT tripMode = TRIP_STOPPED; 
Trip_ModeT chronoMode = TRIP_STOPPED; 
volatile uint8_t trip_timeout = 0;


// Local Variables
// ***************
double timeArray[4] = {MAX_ROTATION_TIME, MAX_ROTATION_TIME, MAX_ROTATION_TIME, MAX_ROTATION_TIME};	/* for averaging the speed */
uint8_t timeIndex = 0;

/*
 ** ===================================================================
 **  Method      :  cyclo_Information
 */
/**
 *  @brief
 *  	After every wheel rotation all informations are recalculated 
 *  	except tripTime, currTime, stopTime, and altitude (see module watch )
 */
/* ===================================================================*/
void cyclo_Information() {
	
	wheelRevo++;

	// current speed calculation
	timeArray[timeIndex++] = rotationTime;
	if (timeIndex >= 4) {
		timeIndex = 0;
	}
	if (rotationTime >= (MAX_ROTATION_TIME-1)) {
		wheelTime = wheelTime + (10 * 1024); // 10 seconds more
		currSpeed = 0.0;
	} else {
		wheelTime = wheelTime + rotationTime * 1024;
		currSpeed = (4.0 * circumference) / (timeArray[0] + timeArray[1] + timeArray[2] + timeArray[3])  ; 		
	}

	// trip/total distance, average speed, and maximum speed
	if (tripMode == TRIP_STARTED) {
		// total distance
		totalDistance = totalDistance + circumference;

		tripDistance = tripDistance + circumference;
		if (currSpeed > maxSpeed) {
			maxSpeed = currSpeed;
		}
		avgSpeed = tripDistance / tripTime;
	}
	
}

/*
 ** ===================================================================
 **  Method      :  cyclo_resetSpeed
 */
/**
 *  @brief
 *  	Resets the speed and the time_array to zero.
 */
/* ===================================================================*/
void cyclo_resetSpeed() {
	uint8_t i;

	currSpeed = 0.0;
	for (i=0; i < 4; i++) {
		timeArray[i] = 0.0;
	}
}

