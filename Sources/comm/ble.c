/**
 *  @brief
 *      Interface to the bluetooth low energy module BL600.
 *      The command line interface use the UART / vSP bridge mode.
 *      The BLE profiles are accessed through the I2C slave interface.
 *      
 *      The UART0 (Resource BL600) is used for communication, default baud rate is 9600. 
 *      The MK22DX does have HW support for CTS/RTS.
 *      Input Buffer size is limited to 100 chars
 *      Output buffer size is limited to 200 chars
 *      
 *      vSP bridge mode
 *      
 *      nAutoRun is GND -> autorun activated
 *      
 *      I2C Communication between BL600 and Bling Bling MCU
 *		The BL600 is Master
 *		High to low transition: Data ready for read
 *		All registers are 32 bit
 *		A write with only 8 bit data sets the register address
 *
 *
 *		Reg
 *	 	-  address	  8bit wr  bit7: auto increment
 *	 	0  state        32bit wr  bit0: BLE link established
 *	 	4  wheelRevo    32bit rd  see CSC measurement
 *	 	8  wheelTime    32bit rd  see CSC measurement
 *	 	12 displayMode  32bit wr
 *	 					   bit0-3   UPPER TOPSIDE
 *		     	           bit4-7   LOWER TOPSIDE
 *				           bit8-11  BLING TOPSIDE
 *				           bit12-15
 *			    	       bit16-19 UPPER BOTTOMSIDE
 *			        	   bit20-23 LOWER BOTTOMSIDE
 *			        	   bit24-27 BLING BOTTOMSIDE
 *			        	   bit28-31
 *	      0  CYCLOCOMPUTER, 1 STRING, 2 IMAGE, 3 LIGHT, 4 BLANK
 *	 	16 cycleMode    32bit wr
 *	 					   bit0-3   UPPER TOPSIDE
 *		     	           bit4-7   LOWER TOPSIDE
 *				           bit8-11  BLING TOPSIDE
 *				           bit12-15
 *			    	       bit16-19 UPPER BOTTOMSIDE
 *			        	   bit20-23 LOWER BOTTOMSIDE
 *			        	   bit24-27 BLING BOTTOMSIDE
 *			        	   bit28-31
 *	 	24 displayColor 32bit wr
 *	 	28 displayImage 32bit wr
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
#include "I2C0.h"

// application include files
// *************************
#include "definitions.h"
#include "ble.h"
#include "powermgr.h"
#include "usb.h"
#include "visual/led.h"
#include "hmi/mode.h"
#include "visual/display.h"
#include "driver/pmeter.h"
#include "cyclo/cyclocomputer.h"


// Global Variables
// ****************
char I2C_Slave_TxBuffer[5] = {0x00, 0x12, 0x34, 0x56, 0x78};
char I2C_Slave_RxBuffer[5] = {0x00, 0x12, 0x34, 0x56, 0x78};
bool ble_LinkState = FALSE;

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
 **  Method      :  ble_show_state
 */
/**     
 *  @brief
 *      shows the Bluetooth link state
 *      
 */
/* ===================================================================*/
void ble_show_state() {
//	if (ble_LinkState) {
//		set_led(TOPSIDE, LED15, BLUE);
//		sleep_wakeup = TRUE;
//	} else {
//		set_led(TOPSIDE, LED15, BLACK);
//	}

    if (BLlink_GetVal(NULL)) {
    	set_led(TOPSIDE, LED15, BLACK);
    } else {
        set_led(TOPSIDE, LED15, BLUE);
        sleep_wakeup = TRUE;
    }


}


/*
 ** ===================================================================
 **  Method      :  ble_I2CblockReceived
 */
/**
 *  @brief
 *      Called by event I2C0_OnSlaveBlockReceived.
 *      If it is only one byte -> register address for sending data
 *      If it is 5 bytes -> register address and 4 data bytes
 */
/* ===================================================================*/
void ble_I2CblockReceived() {
	LDD_I2C_TSize Count;

	Count = I2C0_SlaveGetReceivedDataNum(I2C_DeviceData);
	if (Count == 1) {
		// register address for block to send
		// the register address is in I2C_Slave_RxBuffer[0]
		// prepare data to send
		switch (I2C_Slave_RxBuffer[0]) {
		case STATE_REG:
			// read only
			break;
		case WHEEL_REVO_REG:
			I2C_Slave_TxBuffer[1] =  wheelRevo & 0x000000FF;
			I2C_Slave_TxBuffer[2] = (wheelRevo & 0x0000FF00) >> 8;
			I2C_Slave_TxBuffer[3] = (wheelRevo & 0x00FF0000) >> 16;
			I2C_Slave_TxBuffer[4] = (wheelRevo & 0xFF000000) >> 24;
		case WHEEL_TIME_REG:
			I2C_Slave_TxBuffer[1] =  wheelTime & 0x000000FF;
			I2C_Slave_TxBuffer[2] = (wheelTime & 0x0000FF00) >> 8;
			I2C_Slave_TxBuffer[3] = 0;
			I2C_Slave_TxBuffer[4] = 0;
			break;
		case DISPLAY_MODE_REG:
			I2C_Slave_TxBuffer[1] = displayMode[TOPSIDE][UPPER]    + (displayMode[TOPSIDE][LOWER]    << 4);
			I2C_Slave_TxBuffer[2] = displayMode[TOPSIDE][BLING];
			I2C_Slave_TxBuffer[3] = displayMode[BOTTOMSIDE][UPPER] + (displayMode[BOTTOMSIDE][LOWER] << 4);
			I2C_Slave_TxBuffer[4] = displayMode[BOTTOMSIDE][BLING];
			break;
		}

	} else if (Count == 5) {
		// register address and 4 bytes data
		switch (I2C_Slave_RxBuffer[0]) {
		case STATE_REG:
			ble_LinkState = (I2C_Slave_RxBuffer[1] & BLE_LINK_STATE_BIT) == BLE_LINK_STATE_BIT;
			break;
		case WHEEL_REVO_REG:
			wheelRevo = I2C_Slave_RxBuffer[1]       + I2C_Slave_RxBuffer[2] << 8 +
				        I2C_Slave_RxBuffer[2] << 16 + I2C_Slave_RxBuffer[2] << 24;
			break;
		case WHEEL_TIME_REG:
			wheelTime = I2C_Slave_RxBuffer[1] + I2C_Slave_RxBuffer[2] << 8;
			break;
		case DISPLAY_MODE_REG:
			displayMode[TOPSIDE][UPPER] =     I2C_Slave_RxBuffer[1] & 0x0F;
			displayMode[TOPSIDE][LOWER] =    (I2C_Slave_RxBuffer[1] & 0xF0) >> 4;
			displayMode[TOPSIDE][BLING] =     I2C_Slave_RxBuffer[2] & 0x0F;
			displayMode[BOTTOMSIDE][UPPER] =  I2C_Slave_RxBuffer[3] & 0x0F;
			displayMode[BOTTOMSIDE][LOWER] = (I2C_Slave_RxBuffer[3] & 0xF0) >> 4;
			displayMode[BOTTOMSIDE][BLING] =  I2C_Slave_RxBuffer[4] & 0x0F;
			break;
		}
	} else {
		// not valid
	}

	// prepare slave for receive
	if (I2C0_SlaveReceiveBlock(I2C_DeviceData, I2C_Slave_RxBuffer, 5)) {
		usb_puts("I2C Slave Rx Block: can't set buffer\n");;
	}


}
