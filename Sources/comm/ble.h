/**
 *  @brief
 *      Interface to the blue tooth low energy module BL600.
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
 **  Method      :  ble_link
 */
/**     
 *  @brief
 *      Event handler, called when Bluetooth link is established
 *      
 */
/* ===================================================================*/
void ble_link();

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

#endif /* BLE_H_ */
