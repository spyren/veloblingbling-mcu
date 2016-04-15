/**
 *  @brief
 *      LED driver. There are two rows each 16 multicolor (RGB red, green, and blue) LEDs 
 *      Top row is on the PCB's top side (surface), bottom row is on the PCB's bottom side.
 *
 *  @file
 *      led.c
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

/**
 **  @defgroup led_module LED
 **  @{
 */         

// system include files
// ********************
#include "ctype.h"
#include "stdlib.h"

// PE include files
// ****************
#include "PE_Types.h"
#include "LEDspi.h"
#include "LEDoe.h"
#include "LEDreset.h"


// application include files
// *************************
#include "led.h"
#include "powermgr.h"

// Global Variables
// ****************
volatile bool Led_BlockSent = FALSE;

// Local Variables
// ***************
static LDD_TDeviceData* LEDspiPtr;
static uint64_t LedColumn[BOTTOMSIDE+1];	/**< only the first 48 bits are used */


/*
 ** ===================================================================
 **  Method      :  led_Init
 */
/**
 *  @brief
 *  	Initialises the SPI and clears all LEDs
 */
/* ===================================================================*/
void led_Init() {
	LEDspiPtr = LEDspi_Init(NULL);
	
	// reset the shift register
	LEDreset_ClrVal(NULL);
	LEDreset_SetVal(NULL);
	
	clear_leds(TOPSIDE);
	write_ledColumn(TOPSIDE);
	wait_ledColumn();
	clear_leds(BOTTOMSIDE);
	write_ledColumn(BOTTOMSIDE);
	wait_ledColumn();
	
	// shift register output enable
	LEDoe_ClrVal(NULL);
}


/*
 ** ===================================================================
 **  Method      :  clear_leds
 */
/**
 *  @brief
 *  	clear all LEDs on one side
  *  @param
 *  	surface	top- or bottomside	
 */
/* ===================================================================*/
void clear_leds(surfaceT sur) {
	LedColumn[sur] = 0;
}


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
void set_led(surfaceT surface, LED_nrT nr, LED_colorT color) {
    
	uint64_t Mask = ~ ((uint64_t)07 << (3 * nr));
	uint64_t Set  = (uint64_t)color << (3 * nr);
	LedColumn[surface] = (LedColumn[surface] & Mask) | Set;
}


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
void set_ledColumn(surfaceT surface, uint64_t column) {
    
	LedColumn[surface] = column;
}


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
void write_ledColumn(surfaceT surface) {
	static uint64_t LedSPI[2];
	
	Led_BlockSent = FALSE;
	if (surface == TOPSIDE) {
		LedSPI[0] = ~ LedColumn[0];
		LEDspi_SelectConfiguration(LEDspiPtr, 0, 0);	// top column
		LEDspi_SendBlock(LEDspiPtr, &LedSPI[0], 6);		// send a 48 bit block
	} else {
		LedSPI[1] = ~ LedColumn[1];
		LEDspi_SelectConfiguration(LEDspiPtr, 1, 0);	// bottom column
		LEDspi_SendBlock(LEDspiPtr, &LedSPI[1], 6);		// send a 48 bit block
	}
}

/*
 ** ===================================================================
 **  Method      :  wait_ledColumn
 */
/**
 *  @brief
 *  	Waits till the column is written to the SPI
 *  	For 48 bits it takes about: 
 *  	48 * 0.5 us + overhead = 24 us + 6 us = 30 us 
 */
/* ===================================================================*/
void wait_ledColumn() {
	
	if (standby) {
		return;
	}
	waitTimeout = 2; // start the timeout for 40 ms
	while (!Led_BlockSent  && (waitTimeout) ) {
		// wait for interrupt
		Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
	}
}

	
/**
 ** @}
 */

