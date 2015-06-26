/**
 *  @brief
 *      Set the mode by using the button
 *      
 *  @file
 *      mode.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-20
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
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
