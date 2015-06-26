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
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
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

#endif /* CYCLOCOMPUTER_H_ */
