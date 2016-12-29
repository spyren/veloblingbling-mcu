/**
 *  @brief
 *      Power manager (e.g. interrupt instead of busy wait)
 *      
 *
 *  @file
 *      powermgr.h
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


#ifndef POWERMGR_H_
#define POWERMGR_H_

// PE include files
// ****************
#include "PE_Types.h"

// Global Variables
// ***************
extern volatile bool sleep_wakeup;
extern volatile bool standby;
extern volatile bool low_energy;
extern volatile uint8_t waitTimeout;
extern bool slowHall_Present;


/*
 ** ===================================================================
 **  Method      :  powermgr_Init
 */
/**
 *  @brief
 *  	Initialises the wait counter
 */
/* ===================================================================*/
void powermgr_Init();

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
void wait_int();

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
void wait_10ms(int time);

/*
 ** ===================================================================
 **  Method      :  powermgr_DeepSleep
 */
/**
 *  @brief
 *      Stops the CPU if there is no wheel turn or no Mode button event for more than MAX_SLEEP s. 
 *      CPU goes into Stop mode.
 *      
 *      Called every 10 ms by operation.
 *      Interrupts from BTN1 (Mode Button), ReedInt and RTC1 can wake up the CPU. 
 *      Wakeup Interrupt Controller (WIC) is used to wake from interruptions
 *      
 */
/* ===================================================================*/
void powermgr_DeepSleep();

/*
 ** ===================================================================
 **  Method      :  powermgr_Second
 */
/**
 *  @brief
 *      Clocks the seconds for the sleep timeout.
 *      
 *      Called every second by RTC (Events.c).
 *      
 */
/* ===================================================================*/
void powermgr_Second();

/*
** ===================================================================
**  Method      :  wait_timeout
*/
/**
 *  @brief
 *  	Timeout for busy wait.
 *  	It is called regularly from the USB timer interrupt (500 us)
 *  	
 */
/* ===================================================================*/
void busywait_timeout();


#endif /* POWERMGR_H_ */

