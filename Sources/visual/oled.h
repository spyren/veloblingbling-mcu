/*
 * oled.h
 *
 *  Created on: 29.12.2016
 *      Author: psi
 */

#ifndef OLED_H_
#define OLED_H_

typedef enum {OLED_ON, OLED_OFF, OLED_STANDBY} oled_stateT;

extern bool oled_debug;

/*
 ** ===================================================================
 **  Method      :  oled_Init
 */
/**
 *  @brief
 *  	Initializes the OLED.
 */
/* ===================================================================*/
void oled_Init();

/*
 ** ===================================================================
 **  Method      :  oled_writeWindows
 */
/**
 *  @brief
 *  	Writes all windows data into the OLED DDRAM.
 *      upper top
 *      lower top
 *      blink top
 *      upper bottom
 *      lower bottom
 *      blink bottom
 *
 *      Data format for 16 bit RGB interface:
 *		15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 *		R4 R3 R2 R1 R0 G5 G4 G3 G2 G1 G0 B4 B3 B2 B1 B0

 *
 */
/* ===================================================================*/
void oled_writeWindows();

/*
 ** ===================================================================
 **  Method      :  oled_setState
 */
/**
 *  @brief
 *  	Sets the OLED state (on, off, standby)
 *
 *  @param
 *  	state	OLED_ON, OLED_OFF, OLED_STANDBY
 */
/* ===================================================================*/
void oled_setState(oled_stateT state);

#endif /* OLED_H_ */
