 /**
 *  @brief
 *      Global definitions module
 *  	
 *  	Project wide definitions for Euler Wheel.
 *      
 *  @file
 *      definitions.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-07
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
