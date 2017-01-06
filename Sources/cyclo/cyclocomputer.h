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
 *      incline
 *      temperature
 *      pedaling cadence
 *      
 *  @file
 *      cyclocomputer.h
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

#ifndef CYCLOCOMPUTER_H_
#define CYCLOCOMPUTER_H_

#define TRIP_TIMEOUT 5 /** after 5 s the trip timer will be paused */

typedef enum {CURRENTSPEED, MAXIMUMSPEED, AVERAGESPEED, TRIPDISTANCE, TOTALDISTANCE, 
	CURRENTALTITUDE, TRIPELEVATIONGAIN, TOTALELEVATIONGAIN, MAXALTITUDE, INCLINE, TEMPERATURE, PEDALINGCADENCE,
	CURRENTTIME, CURRENTDATE, TRIPTIME, TOTALTIME, CHRONOTIME, NOCYCLO} Cyclo_modeT;

typedef enum {TRIP_STARTED, TRIP_PAUSED, TRIP_STOPPED} Trip_ModeT;

extern double currSpeed; 			/** [m/s] */
extern double maxSpeed;				/** [m/s] */
extern double avgSpeed;				/** [m/s] */
extern double tripDistance;			/** [m] */
extern double totalDistance;		/** [m] */
extern double currAltitude;			/** [m] */
extern double tripElevationGain;	/** [m] */
extern double totalElevationGain;	/** [m] */
extern double tripElevationLoss;	/** [m] */
extern double totalElevationLoss;	/** [m] */
extern double maxAltitude;			/** [m] */
extern double incline;				/** [m] */
extern double temperature;			/** [°C] degrees centigrade */
extern double cadence;				/** [s^-1] */

extern double altimeterOffset;		/**< altimeter offset [m] */

extern uint32_t wheelRevo;			/**< cumulative wheel revolutions (unitless) */
extern uint16_t wheelTime;			/**< last wheel event time (1/1024 s) */

extern Trip_ModeT tripMode;
extern Trip_ModeT chronoMode;
extern volatile uint8_t trip_timeout;

/*
 ** ===================================================================
 **  Method      :  cyclo_Information
 */
/**
 *  @brief
 *  	After every wheel rotation all informations are recalculated 
 *  	except tripTime, currTime, and stopTime (see module clock)
 */
/* ===================================================================*/
void cyclo_Information();

/*
 ** ===================================================================
 **  Method      :  cyclo_resetSpeed
 */
/**
 *  @brief
 *  	Resets the speed and the time_array to zero.
 */
/* ===================================================================*/
void cyclo_resetSpeed();

#endif /* CYCLOCOMPUTER_H_ */
