/**
 *  @brief
 *  	Displays a pattern all around the wheel except there is
 *  	a window (see module display).
 *  	
 *  	The pattern is about 10 % faster than the wheel
 *      
 *  @file
 *      bling.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-28
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

#ifndef BLING_H_
#define BLING_H_

//extern volatile uint8_t blingLength;
extern volatile bool blingOn[BOTTOMSIDE+1];

/*
 ** ===================================================================
 **  Method      :  bling_Init
 */
/**
 *  @brief
 *  	Initialises the counters
 */
/* ===================================================================*/
void bling_Init();

/*
** ===================================================================
**  Method      :  bling_StartTimer
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (restart counter)
 */
/* ===================================================================*/
void bling_StartTimer();

/*
** ===================================================================
**  Method      :  bling_StopTimer
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (restart counter)
 */
/* ===================================================================*/
void bling_StopTimer();

/*
** ===================================================================
**  Method      :  bling_StartColumn
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (restart counter)
 */
/* ===================================================================*/
void bling_StartColumn();


#endif /* BLING_H_ */
