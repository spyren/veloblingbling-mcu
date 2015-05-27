/**
 *  @brief
 *      Normal operation (automatic mode)
 *      
 *  @file
 *      operation.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-07
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

/**
 **  @defgroup operation_module operation module
 **  @{
 */         
/* MODULE operation */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

// PE include files
// ****************

// application include files
// *************************
#include "powermgr.h"
#include "display.h"
#include "led.h"
#include "usb.h"
#include "button.h"
#include "test.h"
#include "mode.h"
#include "cli.h"


/*
 ** ===================================================================
 **  Method      :  operation
 */
/**
 *  @brief
 *  	Normal operation mode (automatically). Called by main loop.
 *
 *      It returns only when the ESC key (USB) is pressed
 */
/* ===================================================================*/
void operation(void) {	
	usb_puts("Normal operation mode (automatically), hit ESC for command line interface (interactive mode)\n");
	sleep_wakeup = TRUE;
	
	ButtonPressed = FALSE;
	ButtonLongPressed = FALSE;
	
	while (1) {
		if (usb_getc(2) == A_ESC) {
			return;
		}
		// timeout 20 ms
		cli_ble();
		if (ButtonPressed) {
			set_Mode();
		}
		powermgr_DeepSleep();
	}
}	

/**
 ** @}
 */

