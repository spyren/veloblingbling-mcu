/**
 *  @brief
 *      Push button
 *      
 *  Command Line Interface (CLI, interactive mode) for the euler wheel
 *      
 *  @file
 *      button.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-08
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
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
