/**
 *  @brief
 *      LED driver. There are two rows each 16 multicolor (RGB red, green, and blue) LEDs
 *      Top row is on the PCB's top side (surface), bottom row is on the PCB's bottom side.
 *
 *  @file
 *      led.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2013-12-04
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


#ifndef LED_H_
#define LED_H_

/** 16 LEDs */
typedef enum {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16} LED_nrT;

/** lowest (first) bit red, second green, third blue */ 
typedef enum {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE} LED_colorT; 


typedef enum {TOPSIDE, BOTTOMSIDE} surfaceT;

#define RED_MASK 	0x01
#define GREEN_MASK 	0x02
#define BLUE_MASK 	0x04

volatile bool Led_BlockSent;
LDD_TDeviceData* LEDspiPtr;

/*
 ** ===================================================================
 **  Method      :  led_Init
 */
/**
 *  @brief
 *  	Initialises the SPI and clears all LEDs
 */
/* ===================================================================*/
void led_Init();

/*
 ** ===================================================================
 **  Method      :  clear_leds
 */
/**
 *  @brief
 *  	clear all LEDs
  *  @param
 *  	surface	top- or bottomside	
 */
/* ===================================================================*/
void clear_leds(surfaceT surface);

/*
 ** ===================================================================
 **  Method      :  set_led
 */
/**
 *  @brief
 *  	Sets the three LEDs in the multicolor LED according to the specified color
 *  @param
 *  	surface	top- or bottomside
 *  @param
 *      nr  	the LED number (row), from LED1 to LED12
 *  @param
 *      color	the LED color BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE
 *        	
 */
/* ===================================================================*/
void set_led(surfaceT surface, LED_nrT nr, LED_colorT color);

/*
 ** ===================================================================
 **  Method      :  set_ledColumn
 */
/**
 *  @brief
 *  	Sets a LED column
 *  @param
 *  	surface	top- or bottomside
 *  @param
 *      column	the lower 48 bits are the LEDs
 */
/* ===================================================================*/
void set_ledColumn(surfaceT surface, uint64_t column);

/*
 ** ===================================================================
 **  Method      :  write_ledColumn
 */
/**
 *  @brief
 *  	Writes all LEDs in a column to the SPI
 *  @param
 *  	surface		surface
 */
/* ===================================================================*/
void write_ledColumn(surfaceT surface);

/*
 ** ===================================================================
 **  Method      :  wait_ledColumn
 */
/**
 *  @brief
 *  	Waits till the column us written to the SPI
 */
/* ===================================================================*/
void wait_ledColumn(); 

#endif /* LED_H_ */


