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
