 /**
 *  @brief
 *      Global definitions module
 *  	
 *  Project wide definitions for Euler Wheel
 *      
 *  @file
 *      definitions.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-07
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/* Hardware Revisions */
/**********************/

// PROTO1 LEDs only on top side -> no longer supported
// PROTO2 Reed contacts
// PROTO3 Hall sensor, accelerometer
// PROTO4 USB voltage detection
#define HARDWARE PROTO4

#define HALL_SENSOR 1
#define USB_VOLTAGE_DETECTION 1
#define ACCELEROMETER 1

/* ASCII control codes */
/***********************/

#define A_ESC '\x01B'		/**< ASCII Escape code */			
#define A_CR '\x0d'			/**< ASCII Carriage Return code */	
#define A_LF '\x0a'			/**< ASCII Line Feed code */	
#define A_BS '\x08'			/**< ASCII Back Space code */	




#endif /* DEFINITIONS_H_ */
