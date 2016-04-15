/**
 *  @brief
 *      Set the mode by using the button
 *      
 *  @file
 *      mode.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-20
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

#ifndef MODE_H_
#define MODE_H_

#include "visual/display.h"
#include "cyclo/cyclocomputer.h"

extern Display_modeT displayMode[BOTTOMSIDE+1][BLING+1];
extern Cyclo_modeT cycloMode[BOTTOMSIDE+1][BLING+1];
extern char displayString[BOTTOMSIDE+1][BLING+1][40];
extern LED_colorT displayColor[BOTTOMSIDE+1][BLING+1];
extern int displayImage[BOTTOMSIDE+1][BLING+1];
extern bool imperialUnits;											/**< display variables in imperial units */
extern surfaceT surface;

/*
 ** ===================================================================
 **  Method      :  set_Mode
 */
/**
 *  @brief
 *  	Select modes width button
 */
/* ===================================================================*/
void set_Mode();

/*
 ** ===================================================================
 **  Method      :  mode_Update
 */
/**
 *  @brief
 *  	Changes the display in accordance to the modes.
 *  	Called every second.
 */
/* ===================================================================*/
void mode_Update();


#endif /* MODE_H_ */
