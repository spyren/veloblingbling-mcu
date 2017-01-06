/**
 *  @brief
 *      OLED driver.
 *      PM-OLED Display Driver and Controller SEPS114A.
 *      96 x 96 Dots, 65K Colors.
 *
 *      The SPI interface for the bottom side LEDs is also used for the
 *      SEPS114A, but it can't be used at the same time, because the ports
 *      are shared. The top side LEDs can be used.
 *
 *      | *OLED C click*  | *SEPS114A*  | *X6*   | *X7*  | *eWheel*  |
 *      | R/W-            | D3          | 8      |       | GND       |
 *      | RST-            | RSTB-       | 4      |       | SPI-R     |
 *      | CS-             | CSB-        | 3      |       | SPI-STB   |
 *      | SCK pos. edge   | D0          | 5      |       | SPI-CK    |
 *      | SDO             | D2          |        |       |           |
 *      | SDI             | D1          | 6      |       | SPI-OUT   |
 *      | 3.3V            |             |        | 1     | +3V3      |
 *      | GND             | GND         | 8      |       | GND       |
 *      | D/C-            | A0          | 1      |       | SPI-OE    |
 *
 * 		SPI-STT not used (chip select for top side).
 * 		Only write, no read from SEPS114A. R/W- tied to GND.
 * 		SPI-OE is for the LEDs usually low. Set to high only during data communication.
 * 		Index- and Control register 8 bit, memory 16 bit. MSB first.
 *
 * 		SEPS114A Application Note:
 * 		Clock polarity (CPOL) is 0 (low), clock Phase (CPHA) is 1 (change on leading edge).
 * 		mikroElektronika driver:
 * 		Clock idle state low. Serial output data changes on the first clock edge transition.
 *
 *      96 x 96, 6 rows with 16 x 96 pixel, the 4 last pixels are missing.
 *      16 bit colors but only 3 bits used, other 13 bits could be used for brightness.
 *
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
 *  @file
 *      oled.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2016-12-29
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


// system include files
// ********************
#include <stdint.h>
#include <string.h>

// PE include files
// ****************
#include <PE_Error.h>
#include <PE_Types.h>
#include <Cpu.h>
#include <LEDoe.h>
#include <LEDreset.h>
#include <LEDspi.h>

// application include files
// *************************
#include "oled.h"
#include <powermgr.h>
#include <visual/display.h>
#include <visual/led.h>
#include <hmi/mode.h>


#define OLED_CHIP_SELECT		1
#define OLED_8BIT_ATTRIBUTE		1
#define OLED_16BIT_ATTRIBUTE	2

// SEPS114A commands
#define SEPS114A_SOFT_RESET 			0x01
#define SEPS114A_DISPLAY_ON_OFF 		0x02
#define SEPS114A_ANALOG_CONTROL 		0x0F
#define SEPS114A_STANDBY_ON_OFF 		0x14
#define SEPS114A_OSC_ADJUST		 		0x1A
#define SEPS114A_ROW_SCAN_DIRECTION 	0x09
#define SEPS114A_DISPLAY_X1 			0x30
#define SEPS114A_DISPLAY_X2 			0x31
#define SEPS114A_DISPLAY_Y1 			0x32
#define SEPS114A_DISPLAY_Y2 			0x33
#define SEPS114A_DISPLAYSTART_X 		0x38
#define SEPS114A_DISPLAYSTART_Y 		0x39
#define SEPS114A_CPU_IF 				0x0D
#define SEPS114A_MEM_X1 				0x34
#define SEPS114A_MEM_X2 				0x35
#define SEPS114A_MEM_Y1 				0x36
#define SEPS114A_MEM_Y2 				0x37
#define SEPS114A_MEMORY_WRITE_READ 		0x1D
#define SEPS114A_DDRAM_DATA_ACCESS_PORT 0x08
#define SEPS114A_DISCHARGE_TIME 		0x18
#define SEPS114A_PEAK_PULSE_DELAY 		0x16
#define SEPS114A_PEAK_PULSE_WIDTH_R 	0x3A
#define SEPS114A_PEAK_PULSE_WIDTH_G 	0x3B
#define SEPS114A_PEAK_PULSE_WIDTH_B 	0x3C
#define SEPS114A_PRECHARGE_CURRENT_R 	0x3D
#define SEPS114A_PRECHARGE_CURRENT_G 	0x3E
#define SEPS114A_PRECHARGE_CURRENT_B 	0x3F
#define SEPS114A_COLUMN_CURRENT_R 		0x40
#define SEPS114A_COLUMN_CURRENT_G 		0x41
#define SEPS114A_COLUMN_CURRENT_B 		0x42
#define SEPS114A_ROW_OVERLAP 			0x48
#define SEPS114A_SCAN_OFF_LEVEL 		0x49
#define SEPS114A_ROW_SCAN_ON_OFF 		0x17
#define SEPS114A_ROW_SCAN_MODE 			0x13
#define SEPS114A_SCREEN_SAVER_CONTROL 	0xD0
#define SEPS114A_SS_SLEEP_TIMER 		0xD1
#define SEPS114A_SCREEN_SAVER_MODE 		0xD2
#define SEPS114A_SS_UPDATE_TIMER 		0xD3
#define SEPS114A_RGB_IF 				0xE0
#define SEPS114A_RGB_POL 				0xE1
#define SEPS114A_DISPLAY_MODE_CONTROL 	0xE5


// Global Variables
// ****************
bool oled_debug = FALSE;

// Local Variables
// ***************

/*
  ** ===================================================================
  **  Method      :  seps_command
  */
 /**
  *  @brief
  *  	Sends a command to OLED C display driver SEPS114A.
  *  	Blocking write.
  */
 /* ===================================================================*/
 static void seps_command(uint8_t reg_index, uint8_t reg_value){

     if (LEDspi_SelectConfiguration(LEDspiPtr, OLED_CHIP_SELECT, OLED_8BIT_ATTRIBUTE) != ERR_OK) {
    	 return;
     }

	 // Select index address
	 LEDoe_ClrVal(NULL);	// command
     if (LEDspi_SendBlock(LEDspiPtr, &reg_index, 1) != ERR_OK) {
    	 return;
     }
     while(!Led_BlockSent) {
    	 // no timeout -> dangerous but it is only used for debugging
    	 Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
     }
     Led_BlockSent = FALSE;

     // Write data to register
	 LEDoe_SetVal(NULL);	// data
	 if (LEDspi_SendBlock(LEDspiPtr, &reg_value, 1) != ERR_OK) {
    	 LEDoe_ClrVal(NULL);	// default low
    	 return;
	 }
     while(!Led_BlockSent) {
    	 // no timeout -> dangerous but it is only used for debugging
    	 Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
     }
     Led_BlockSent = FALSE;

	 LEDoe_ClrVal(NULL);	// default low
 }

 /*
  ** ===================================================================
  **  Method      :  seps_ddram
  */
 /**
  *  @brief
  *  	Before writing to the DDRAM.
  *  	Blocking write.
  */
 /* ===================================================================*/
 static void seps_ddram(){

	 uint8_t data = SEPS114A_DDRAM_DATA_ACCESS_PORT;

     if (LEDspi_SelectConfiguration(LEDspiPtr, OLED_CHIP_SELECT, OLED_8BIT_ATTRIBUTE) != ERR_OK) {
    	 return;
     }

     // Write data to register
	 LEDoe_ClrVal(NULL);	// data
	 if (LEDspi_SendBlock(LEDspiPtr, &data, 1) != ERR_OK) {
		 return;
	 }
     while(!Led_BlockSent) {
    	 // no timeout -> dangerous but it is only used for debugging
    	 Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
     }
     Led_BlockSent = FALSE;
 }


/*
 ** ===================================================================
 **  Method      :  write16PixelColumn
 */
/**
 *  @brief
 *  	Writes a 16 pixel column into the OLED DDRAM.
 *  	For 16 x 16 bits it takes about:
 *  	256 * 0.5 us + overhead = 128 us + 22 us = 150 us
 *
 *  @param
 *  	column_p	pointer to the 16 Word buffer
 *  	x			x coordinate (upper left corner)
 *  	y			y coordinate (upper left corner)
 */
/* ===================================================================*/
static void write16PixelColumn(uint16_t * column_p, uint8_t x, uint8_t y) {
	static uint16_t column_a[16];	// has to be static because of non-blocking SPI

	// wait till data block is sent
	while(!Led_BlockSent) {
		// no timeout -> dangerous but it is only used for debugging
		Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
	}
	Led_BlockSent = FALSE;

	memcpy(column_a, column_p, sizeof(column_a));
	seps_command(SEPS114A_MEM_X1, x);
	seps_command(SEPS114A_MEM_X2, x);
	seps_command(SEPS114A_MEM_Y1, y);
	seps_command(SEPS114A_MEM_Y2, y + 15);

	seps_ddram();

	// non-blocking SPI 16 * 16 bit
    if (LEDspi_SelectConfiguration(LEDspiPtr, OLED_CHIP_SELECT, OLED_16BIT_ATTRIBUTE) != ERR_OK) {
    	return;
    }
	Led_BlockSent = FALSE;
	LEDoe_SetVal(NULL);	// data
	if (LEDspi_SendBlock(LEDspiPtr, column_a, 16) != ERR_OK) {
		return;
	}
	// LEDoe_ClrVal(NULL);	// default low
}

/*
 ** ===================================================================
 **  Method      :  oled_Init
 */
/**
 *  @brief
 *  	Initializes the OLED.
 *  	See also
 */
/* ===================================================================*/
void oled_Init() {
	if (!oled_debug) {
		// without OLED there is nothing to do
		return;
	}

	LEDreset_ClrVal(NULL);		// Hardware reset
	wait_10ms(2);
	LEDreset_SetVal(NULL);
	wait_10ms(5);
	/*  Soft reset */
	seps_command(SEPS114A_SOFT_RESET, 0x00);
	/* Standby ON/OFF*/
	seps_command(SEPS114A_STANDBY_ON_OFF, 0x01);         	// Standby on
	wait_10ms(1);
	seps_command(SEPS114A_STANDBY_ON_OFF, 0x00);          	// Standby off
	wait_10ms(1);
	/* Display OFF */
	seps_command(SEPS114A_DISPLAY_ON_OFF, 0x00);
	/* Set Oscillator operation */
	seps_command(SEPS114A_ANALOG_CONTROL, 0x00);          	// using external resistor and internal OSC
	/* Set frame rate */
	seps_command(SEPS114A_OSC_ADJUST, 0x03);              	// frame rate : 95Hz
	/* Set active display area of panel */
	seps_command(SEPS114A_DISPLAY_X1, 0x00);
	seps_command(SEPS114A_DISPLAY_X2, 0x5F);
	seps_command(SEPS114A_DISPLAY_Y1, 0x00);
	seps_command(SEPS114A_DISPLAY_Y2, 0x5F);
	/* Select the RGB data format and set the initial state of RGB interface port */
	seps_command(SEPS114A_RGB_IF, 0x00);                 	// RGB 8bit interface
	/* Set RGB polarity */
	seps_command(SEPS114A_RGB_POL, 0x00);
	/* Set display mode control */
	seps_command(SEPS114A_DISPLAY_MODE_CONTROL, 0x80);   	// SWAP:BGR, Reduce current : Normal, DC[1:0] : Normal
	/* Set MCU Interface */
	seps_command(SEPS114A_CPU_IF, 0x00);                 	// MPU External interface mode, 8bits (0x01 16 bits?)
	/* Set Memory Read/Write mode */
	// VH= 0, The data is continuously written horizontally
	// MDIR1= 0, Vertical address counter is increased
	// MDIR0= 0, Horizontal address counter is increased
	seps_command(SEPS114A_MEMORY_WRITE_READ, 0x00);
	/* Set row scan direction */
	seps_command(SEPS114A_ROW_SCAN_DIRECTION, 0x00);     	// Column : 0 --> Max, Row : 0 --> Max
	/* Set row scan mode */
	seps_command(SEPS114A_ROW_SCAN_MODE, 0x00);          	// Alternate scan mode
	/* Set column current */
	seps_command(SEPS114A_COLUMN_CURRENT_R, 0x6E);
	seps_command(SEPS114A_COLUMN_CURRENT_G, 0x4F);
	seps_command(SEPS114A_COLUMN_CURRENT_B, 0x77);
	/* Set row overlap */
	seps_command(SEPS114A_ROW_OVERLAP, 0x00);            	// Band gap only
	/* Set discharge time */
	seps_command(SEPS114A_DISCHARGE_TIME, 0x01);         	// Discharge time : normal discharge
	/* Set peak pulse delay */
	seps_command(SEPS114A_PEAK_PULSE_DELAY, 0x00);
	/* Set peak pulse width */
	seps_command(SEPS114A_PEAK_PULSE_WIDTH_R, 0x02);
	seps_command(SEPS114A_PEAK_PULSE_WIDTH_G, 0x02);
	seps_command(SEPS114A_PEAK_PULSE_WIDTH_B, 0x02);
	/* Set precharge current */
	seps_command(SEPS114A_PRECHARGE_CURRENT_R, 0x14);
	seps_command(SEPS114A_PRECHARGE_CURRENT_G, 0x50);
	seps_command(SEPS114A_PRECHARGE_CURRENT_B, 0x19);
	/* Set row scan on/off  */
	seps_command(SEPS114A_ROW_SCAN_ON_OFF, 0x00);        	// Normal row scan
	/* Set scan off level */
	seps_command(SEPS114A_SCAN_OFF_LEVEL, 0x04);         	// VCC_C*0.75
	/* Set memory access point */
	seps_command(SEPS114A_DISPLAYSTART_X, 0x00);
	seps_command(SEPS114A_DISPLAYSTART_Y, 0x00);
	/* Display ON */
	seps_command(SEPS114A_DISPLAY_ON_OFF, 0x01);
}

/*
 ** ===================================================================
 **  Method      :  oled_writeWindows
 */
/**
 *  @brief
 *  	Writes all 6 windows data into the OLED DDRAM.
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
 *		It takes about 96 x 16 x 150 us = 230 ms
 *
 */
/* ===================================================================*/
void oled_writeWindows() {
	uint16_t column_a[16];
	uint8_t row, row_i;
	uint8_t column, column_i, y;
	windowT win;
	surfaceT surface;
	uint64_t LED_column;

	if (!oled_debug) {
		// without OLED there is nothing to do
		return;
	}

	// seps_command(SEPS114A_CPU_IF, 0x00);
	Led_BlockSent = TRUE;
	for (surface = TOPSIDE; surface < BOTTOMSIDE+1; surface++) {
		for (win = UPPER; win < BLING+1; win++) {
			y = 80 - (win + (surface * 3)) * 16;
			for (column = 0; column < 96; column++) {
				if (displayMode[surface][win] == BLANK) {
					// blank line
					memset(column_a, 0x00, sizeof(column_a));
				} else {
					if (win == BLING) {
						// repeat the image
						column_i = column % display[surface][win].length;
					} else {
						column_i = column;
					}
					LED_column = display[surface][win].dotmatrix[column_i];
					for (row = 0; row < 16; row++) {
						if (win == LOWER) {
							// lower window is upside down
							row_i = 15 - row;
						} else {
							row_i = row;
						}
						column_a[row_i] = 0;
						// red
						if (LED_column & (uint64_t) 0b0001) {
							column_a[row_i] |= 0b1111100000000000;
						}
						LED_column = LED_column >> 1;
						// green
						if (LED_column & (uint64_t) 0b0001) {
							column_a[row_i] |= 0b0000011111100000;
						}
						LED_column = LED_column >> 1;
						// blue
						if (LED_column & (uint64_t) 0b0001) {
							column_a[row_i] |= 0b0000000000011111;
						}
						LED_column = LED_column >> 1;
					}
				}
				// 				// all red (for testing purposes)
				//				write16PixelColumn(column_a, column, y);
				//				for (row = 0; row < 16; row++) {
				//					column_a[row] = 0b1111100000000000; // red
				//				}
				write16PixelColumn(column_a, column, y);
			}
		}
	}
}


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
void oled_setState(oled_stateT state) {
	if (oled_debug) {
		switch (state) {
		case OLED_ON:
			// Screen Saver OFF
			seps_command(SEPS114A_SCREEN_SAVER_CONTROL, 0x00);
			// Display ON
			seps_command(SEPS114A_DISPLAY_ON_OFF, 0x01);
			break;
		case OLED_OFF:
			// Display OFF
			seps_command(SEPS114A_DISPLAY_ON_OFF, 0x00);
			break;
		case OLED_STANDBY:
			// Display ON
			seps_command(SEPS114A_DISPLAY_ON_OFF, 0x01);
			// Screen Saver ON
			seps_command(SEPS114A_SCREEN_SAVER_CONTROL, 0x80);
			break;
		}
	}
}

