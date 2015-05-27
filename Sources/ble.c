/**
 *  @brief
 *      Interface to the blue tooth low energy module BL600.
 *      
 *      The UART0 (Resource BL600) is used for communication, default baud rate is 9600. 
 *      The MKL25Z does not have HW support for CTS/RTS, 
 *      handshaking is SW emulated (not implemented yet).
 *      Input Buffer size is limited to 100 chars
 *      Output buffer size is limited to 200 chars
 *      
 *      vSP bridge mode
 *      
 *      nAutoRun is GND -> autorun activated
 *      
 *  @file
 *      ble.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-05-13
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

/**
 **  @defgroup ble_module blue tooth low energy module
 **  @{
 */         
/* MODULE ble */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

// PE include files
// ****************
#include "PE_Types.h"
#include "BLreset.h"
#include "BLlink.h"
#include "BL600.h"

// application include files
// *************************
#include "definitions.h"
#include "ble.h"
#include "powermgr.h"
#include "usb.h"
#include "led.h"


// Global Variables
// ****************

// Local Variables
// ***************
static const char run_bling_s[] = "at+run \"bling\"\r";		// run the Bling vSP application
static const char run_lowpower_s[] = "at+run \"lp\"\r";  	// run the Low Power application


/*
 ** ===================================================================
 **  Method      :  ble_Init
 */
/**
 *  @brief
 *  	Initialises the blue tooth low energy module BL600
 *  @return
 *  	0			success
 *  	-1			can't send
 *  	-2			can't receive
 *  	-3			wrong answer
 */
/* ===================================================================*/
int ble_Init() {
	int error;
	char answer[100];
	
	ble_reset();
	
	// UART_RTS_PutVal(NULL, FALSE);	// hardware handshake, ready to receive data
	
	// error = ble_command("ati 3\r", answer, sizeof(answer));
	// error = ble_command("ati 49406\r", answer, sizeof(answer));
	error = ble_command(run_bling_s, answer, sizeof(answer));
	if (strstr(answer, "OK") == NULL) {
		error = -3;
	} else {
		error = 0;
	}
 	
	return error;
}


/*
 ** ===================================================================
 **  Method      :  ble_lowPower
 */
/**
 *  @brief
 *  	Initialises the blue tooth low energy module BL600 to
 *  	low power mode (everything is switched off)
 */
/* ===================================================================*/
void ble_lowPower() {
	int error;
	char answer[100];

	ble_reset();

	// UART_RTS_PutVal(NULL, FALSE);	// hardware handshake, ready to receive data

	error = ble_command(run_lowpower_s, answer, sizeof(answer));
}


/*
 ** ===================================================================
 **  Method      :  ble_reset
 */
/**
 *  @brief
 *  	Resets the blue tooth low energy module BL600.
 *  	The reset pin is normally input, otherwise it is not possible 
 *  	to use JTAG for the BL600 module.
 */
/* ===================================================================*/
void ble_reset() {
	BLreset_SetOutput(NULL);
	BLreset_PutVal(NULL, FALSE);
	wait_10ms(4);
	BLreset_PutVal(NULL, TRUE);	
	BLreset_SetInput(NULL);

	wait_10ms(100);
}

/*
 ** ===================================================================
 **  Method      :  ble_onFullRxBuf
 */
/**
 *  @brief
 *  	Event handler, called when UART RX buffer full
 *  	-> set the CTS
 */
/* ===================================================================*/
void ble_onFullRxBuf() {
	// UART_RTS_PutVal(NULL, TRUE);	// hardware handshake, can't receive data
}


/*
 ** ===================================================================
 **  Method      :  ble_command
 */
/**
 *  @brief
 *  	Sends a command (e.g. a ATI command) to the BL600
 *  @parameter
 *  	command		command string
 *  @parameter
 *  	answer		answer string from BL600
 *  @parameter
 *  	len			max. answer length
 *  @return
 *  	0			success
 *  	-1			can't send
 *  	-2			can't receive
 */
/* ===================================================================*/
int ble_command(const char *command, char *answer, int len) {
	word count = 0;
	word rxchars;
	int error;
	
	strcpy(answer, "");
	error = ble_puts(command);
	if (error < 0) {
		return -1;
	}
	
	wait_10ms(20);
	rxchars = BL600_GetCharsInRxBuf();
	if (rxchars >= len) {
		error = BL600_RecvBlock((BL600_TComData*) answer, len-1, &count);
	} else {
		error = BL600_RecvBlock((BL600_TComData*) answer, rxchars, &count);
	}
		
	answer[count] = 0;
	
	return error;
}


/*
 ** ===================================================================
 **  Method      :  ble_puts
 */
/**     
 *  @brief
 *      Write a string s to the BLE Module over UART 
 *      
 *  @parameter
 *  	s	string to write    
 *  @return
 *  	>= 0	number of characters written
 *  	<0		error
 */
/* ===================================================================*/
int ble_puts(const char *s) {
	word count;
	byte error;
	
	error = BL600_SendBlock((BL600_TComData*) s, strlen(s), &count);
	if (error == ERR_OK) {
		return count;
	} else {
		return -count;
	}
}


/*
 ** ===================================================================
 **  Method      :  ble_link
 */
/**     
 *  @brief
 *      Event handler, called when Bluetooth link is established
 *      
 */
/* ===================================================================*/
void ble_link() {
	sleep_wakeup = TRUE;
}

/*
 ** ===================================================================
 **  Method      :  ble_show_state
 */
/**     
 *  @brief
 *      shows the Bluetooth link state
 *      
 */
/* ===================================================================*/
void ble_show_state() {
	if (BLlink_GetVal(NULL)) {
		set_led(TOPSIDE, LED15, BLACK);
	} else {
		set_led(TOPSIDE, LED15, BLUE);
		sleep_wakeup = TRUE;
	}
}
