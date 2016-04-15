/**
 *  @brief
 *      Push button interface.
 *      
 *  @file
 *      button.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-08
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

#ifndef BUTTON_H_
#define BUTTON_H_

#include "PE_Types.h"
//#include "string.h"
//#include "ctype.h"
//#include "stdlib.h"
//#include "BTN1.h"

extern volatile bool ButtonState;		// TRUE as long as the key is pressed
extern volatile bool ButtonPressed;		// TRUE after the key is pressed (must be cleared by reader)
extern volatile bool ButtonReleased;		// TRUE after the key is released (must be cleared by reader)
extern volatile bool ButtonLongPressed;	// TRUE after the key is pressed longer than 1 s (must be cleared by reader)


/* ===================================================================
 *     Method      :  button_Task
 */
/**
 *   @brief
 *      Button task function. 
 *      It is called regularly from a timer interrupt (every 500 us)
 *
 */
/* ===================================================================*/
void button_Task();

#endif /* BUTTON_H_ */
