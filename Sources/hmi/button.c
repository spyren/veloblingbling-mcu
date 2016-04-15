/**
 *  @brief
 *      Push button interface.
 *      
 *  @file
 *      button.c
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

/**
 **  @defgroup button_module Push Button module
 **  @{
 */         
/* MODULE button */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

// PE include files
// ****************
#include "ModeButton.h"

// application include files
// *************************
#include "definitions.h"
#include "powermgr.h"

// Global Variables
// ****************
volatile bool ButtonState = FALSE;			// last state
volatile bool ButtonPressed = FALSE;
volatile bool ButtonReleased = FALSE;
volatile bool ButtonLongPressed = FALSE;

// Local Variables
// ***************
static uint8_t buttonTimeout = 0;
static uint16_t buttonLongTimeout = 0;

/* ===================================================================
 *     Method      :  button_Task
 */
/**
 *   @brief
 *      Button task function. 
 *      It is called regularly from the tick timer interrupt (every 20 ms)
 *
 */
/* ===================================================================*/
void button_Task() {
	if (buttonTimeout++ >= 3) {
		// 60 ms sample rate
		buttonTimeout = 0;
		bool buttonVal;
		
		buttonVal = ! ModeButton_GetVal(NULL);
		
		if (ButtonState) {
			// last sample pressed
			if (buttonVal) {
				// button still pressed
				buttonLongTimeout++;
				if (buttonLongTimeout == 17) {  // about 1 s
					// button 1 s pressed
					ButtonLongPressed = TRUE;	
				}
			} else {
				// button no longer pressed -> button released
				ButtonReleased = TRUE;
				buttonLongTimeout = 0;
			}
		} else {
			// last sample not pressed
			if (buttonVal) {
				// button pressed 
				ButtonPressed = TRUE;
			} else {
				// button not pressed -> nothing to do
			}
			
		}

		ButtonState = buttonVal;
	}
}

/**
 ** @}
 */

