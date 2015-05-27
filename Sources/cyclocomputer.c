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
#include "usb.h"
#include "wheelsensor.h"
#include "watch.h"

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

Trip_ModeT tripMode = TRIP_STOPPED; 
Trip_ModeT chronoMode = TRIP_STOPPED; 
volatile uint8_t trip_timeout = 0;


// Local Variables
// ***************
double timeArray[4] = {0.0, 0.0, 0.0, 0.0};	/* for averaging the speed */
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
	
	// current speed calculation
	if (rotationTime < 0.0) {
		currSpeed = 0.0;
	} else {
		timeArray[timeIndex++] = rotationTime;
		if (timeIndex >= 4) {
			timeIndex = 0;
		}
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



