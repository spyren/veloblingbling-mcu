/**
 *  @brief
 *      Command Line Interface (CLI, interactive mode)
 *      
 *  Command Line Interface (CLI, interactive mode) for the euler wheel
 *      
 *  @file
 *      cli.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2013-12-04
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef CLI_H_
#define CLI_H_

#include "PE_Types.h"

// Timeout 60 s
#define CLI_TIMEOUT 60000


// types
// *****

/* Operating Mode */
/******************/

/** the system can be only in these operating modes */
typedef enum {NORMAL, INTERACTIVE_USB, INTERACTIVE_BLE, TESTING, MODE_BUTTON} operating_modeT;

typedef enum {USB_CHANNEL, BLE_CHANNEL, SCRIPT_CHANNEL} channelT;


extern operating_modeT operating_mode;

extern int TimeOut;
extern bool wheelDetection;

extern const char helloMessage[];

/*  ===================================================================
 *     Method      :  puts_ch
 */
/**
 *  @brief
 *      Write a string s to the serial channel
 */
/* ===================================================================*/
void puts_ch(const char *s, channelT ch);

/*
 ** ===================================================================
 **  Method      :  cli_parse
 */
/**
 *  @brief
 *      Command line interface
 *
 *  Command line interface. Reads the line and interprets the
 *  command. With command 'exit' the function returns 1, otherwise 0.
 *  - exit<br>
 *  - test<br>
 *  - show
 *  - set
 *  - uptime<br>
 *  - fault<br>
 *  - reset<br>
 *  - help [<command>]
 *  @param
 *  	line	command line
 *  	ch		output channel (USB or BLE)
 *  @return
 *  	0	OK
 *  	1	Exit command
 *
 */
/* ===================================================================*/
int cli_parse(char * line, channelT ch);

/*
 ** ===================================================================
 **  Method      :  cli_usb
 */
/**
 *  @brief
 *      Command line interface over USB
 *
 *  Command line interface. Reads the USB console and interprets the
 *  commands. With command 'exit' the function returns.
 *  
 *  USB has priority over BLE.
 *  
 *  Called by main-loop (ProcessorExpert)
 *  
 */
/* ===================================================================*/
void cli_usb();

/*
 ** ===================================================================
 **  Method      :  cli_ble
 */
/**
 *  @brief
 *      Command line interface over BLE
 *
 *  Command line interface. Reads the BLE vSP and interprets the
 *  commands.
 *  
 *  Called every 10 ms by operation (not called as long as USB is active)
 *  
 */
/* ===================================================================*/
void cli_ble();

#endif /* CLI_H_ */
