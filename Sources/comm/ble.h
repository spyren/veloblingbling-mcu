/**
 *  @brief
 *      Interface to the bluetooth low energy module BL600.
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
 *  @file
 *      ble.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-05-13
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */


#ifndef BLE_H_
#define BLE_H_

#define BLE_INPUT_BUFFER_SIZE	100
#define BLE_OUTPUT_BUFFER_SIZE	200

#define BLE_LINK_STATE_BIT 0x01

#define SLAVE_ADDRESS		0	// I2C address

#define STATE_REG			0	// state register
#define WHEEL_REVO_REG		4	// wheelRevo register
#define WHEEL_TIME_REG		8	// wheelTime register
#define DISPLAY_MODE_REG	12	// displayMode register
#define CYCLE_MODE_REG		16	// cycleMode register
#define DISPLAY_COLOR_REG	20	// displayColor register
#define DISPLAY_IMAGE_REG	24	// displayImage register

#define DISPLAY_MODE_MOD	1	// displayMode modified
#define CYCLE_MODE_MOD		2	// cycleMode modified
#define DISPLAY_COLOR_MOD	4	// displayColor modified
#define DISPLAY_IMAGE_MOD	8	// displayImage modified


// Global Variables
// ****************
extern char I2C_Slave_TxBuffer[];
extern char I2C_Slave_RxBuffer[];
extern bool ble_LinkState;

/*
 ** ===================================================================
 **  Method      :  ble_Init
 */
/**
 *  @brief
 *  	Initialises the blue tooth low energy module BL600
 */
/* ===================================================================*/
int ble_Init();

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
void ble_lowPower();

/*
 ** ===================================================================
 **  Method      :  ble_reset
 */
/**
 *  @brief
 *  	Resets the blue tooth low energy module BL600
 */
/* ===================================================================*/
void ble_reset();

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
void ble_onFullRxBuf();

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
int ble_command(const char *command, char *answer, int len);

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
int ble_puts(const char *s);

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
void ble_show_state();

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
void ble_I2CblockReceived();

#endif /* BLE_H_ */
