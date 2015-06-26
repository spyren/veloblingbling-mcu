/**
 *  @brief
 *      Calculates time related informations for the cyclocomputer.
 *      
 *      trip time
 *      current time
 *      stopwatch
 *      
 *  @file
 *      watch.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef WATCH_H_
#define WATCH_H_

extern double tripTime;		/** trip time [s] */
extern double currTime;		/** current time [s] */
extern double chronoTime;	/** stop (chrono) watch time [s] */
extern double totalTime;	/**< total time [s] */
extern double upTime;		/**< up time [s] */

extern LDD_RTC_TTime watchTime; /**< watch time */

extern char timeStr[];		/**< HH:MM:SS */
extern char dateStr[];     	/**< DD:MM:YYYY */

extern LDD_TDeviceData* watchPtr;

/*
 ** ===================================================================
 **  Method      :  watch_Init
 */
/**
 *  @brief
 *  	Initialises the real time counter
 */
/* ===================================================================*/
void watch_Init();

/*
 ** ===================================================================
 **  Method      :  watch_Synch
 */
/**
 *  @brief
 *  	Interrupt from RTC1 (every second).
 */
/* ===================================================================*/
void watch_Synch();

#endif /* WATCH_H_ */
