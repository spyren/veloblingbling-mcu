/**
 *  @brief
 *  	Write strings to the dot matrix and display columns.
 *
 *      The character height is 16 pixel (max 21 pixel)
 *      There are 100 columns:
 *        20 chars in 5x12 font,
 *        16 chars in 6x8 font,
 *        14 chars in 7x12 font,
 *        12 chars in 8x12 font,
 *        8  chars in 12x16 font
 *
 *		Codepage 850, IBM PC character set
 *		  850             ISO-8859  Unicode  UTF-8
 *		ä 132 0x84 o204   E4        U+00E4   C3 A4
 *		ö 148 0x94 o224   F6        U+00F6   C3 B6
 *		ü 129 0x81 o201   FC        U+00FC   C3 BC
 *		° 248 0xF8 o370   B0        U+00B0   C2 B0
 *
 *  @file
 *      display.c
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
 **  @defgroup display_module display
 **  @{
 */
/* MODULE display */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

// PE include files
// ****************
#include "PE_Types.h"
#include "FlashMem.h"

// application include files
// *************************
#include "display.h"
#include "led.h"
#include "oled.h"
#include "5x12_vertikal_MSB_1.h"
#include "6x8_vertikal_MSB_1.h"
#include "7x12_vertikal_MSB_1.h"
#include "7x12b_vertikal_MSB_1.h"
#include "8x12_vertikal_MSB_1.h"
#include "12x16_vertikal_MSB_1.h"
#include "hmi/mode.h"
#include "motion/bling.h"
#include "driver/parameter.h"
#include "comm/usb.h"
#include "motion/wheelsensor.h"


#define WHITE_COLUMN ((uint64_t)07777777777777777)
#define RED_COLUMN ((uint64_t)01111111111111111)


// Global Variables
// ****************
image_s (*imageP)[50];
image_s *image_bufferP;

/**
 * 20 char in 5x12, 14 char in 7x12, 12 char in 8x12, 8 char in 12x16 (100 y dots)
 * Dimensions: Surface, Window, Column, Rows are grouped in 3 bits
 * Window dimension:
 *   the first dotmatrix is the UPPER window,
 *   the second dotmatrix is the LOWER window,
 *   the third dotmatrix is the (bling)-pattern
 */
image_s display[BOTTOMSIDE+1][BLING+1];

/*
12 in 8x12
: in 5x12
A in 12x16

        0 1 2 3 4 5 6 7 8 9 A B C D E F101122131415161718191A1B1C1D1E1F2021..
F 8000 --------------------------------------------         XXXX
E 4000 --------------------------------------------         XXXX
D 2000 --------------------------------------------       XXXXXXXX
C 1000 --------------------------------------------       XXXXXXXX
B 0800                                                    XXXXXXXX
A 0400     XX           XXXXXXXX                        XXXXXXXXXXXX
9 0200   XXXX         XXXX    XXXX                      XXXX    XXXX
8 0100 XXXXXX         XXXX    XXXX                      XXXX    XXXX
7 0080     XX                 XXXX        XXXX        XXXX        XXXX
6 0040     XX               XXXX          XXXX        XXXXXXXXXXXXXXXX
5 0020     XX             XXXX                        XXXXXXXXXXXXXXXX
4 0010     XX           XXXX                        XXXX            XXXX
3 0008     XX         XXXX    XXXX        XXXX      XXXX            XXXX
2 0004 XXXXXXXXXXX----XXXXXXXXXXXX----    XXXX----  XXXX            XXXX--
1 0002
0 0001
*/


// Local Variables
// ***************

// from left to right, bottom to top
static const LED_colorT France[3] =  {BLUE, WHITE, RED};
static const LED_colorT Germany[3] = {YELLOW, RED, BLACK};
static const LED_colorT Belgium[3] = {BLACK, YELLOW, RED};
static const LED_colorT Austria[3] = {RED, WHITE, RED};
static const LED_colorT Spain[3] =   {RED, YELLOW, RED};
static const LED_colorT Italy[3] =   {GREEN, WHITE, RED};

static const uint64_t swiss_pattern[16] = {
	01111111111111111, // octal!
	01111111111111111,
	01111117777111111,
	01111117777111111,
	01111117777111111,
	01111117777111111,
	01177777777777711,
	01177777777777711,
	01177777777777711,
	01177777777777711,
	01111117777111111,
	01111117777111111,
	01111117777111111,
	01111117777111111,
	01111111111111111,
	01111111111111111,
};

static const uint64_t heart_pattern[16] = {
	00000111100000000,   // 0
	00001111111000000,   // 1
	00011111111100000,   // 2
	00111111111110000,   // 3
	00111111111111000,   // 4
	00111111111111100,   // 5
	00011111111111110,   // 6
	00001111111111111,   // 7
	00001111111111111,   // 8
	00011111111111110,   // 9
	00111111111111100,   // 10
	00111111111111000,   // 11
	00111111111110000,   // 12
	00011111111100000,   // 13
	00001111111000000,   // 14
	00000111100000000    // 15
};
static const uint64_t heart_pattern_r[16] = {
	00000000011110000,   // 0
	00000001111111000,   // 1
	00000011111111100,   // 2
	00000111111111110,   // 3
	00001111111111110,   // 4
	00011111111111110,   // 5
	00111111111111100,   // 6
	01111111111111000,   // 7
	01111111111111000,   // 8
	00111111111111100,   // 9
	00011111111111110,   // 10
	00001111111111110,   // 11
	00000111111111110,   // 12
	00000011111111100,   // 13
	00000001111111000,   // 14
	00000000011110000    // 15
};

static const uint64_t snow_pattern[16] = {
	00000070007000000,	// octal!
	00007000000000000,
	00000000000000000,
	00000070000000000,
	00700000000070000,
	00000000000000000,
	00000000070000000,
	00007000000070000,
	00000000000000000,
	00000007000000000,
	00000000000000000,
	00070000700000000,
	00000000000070000,
	00070070000000000,
	00000000000000070,
	00007000000000000,
};

static const uint64_t meander_pattern[8] = {
    01010000000100000,	// octal
    01011111110100000,
    01000000010100000,
    01011111010100000,
    01010001010100000,
    01010111010100000,
    01010100010100000,
    01010111110100000
};


/*
 ** ===================================================================
 **  Method      :  display_Init
 */
/**
 *  @brief
 *  	Initialises the display.
 */
/* ===================================================================*/
void display_Init() {
	//init_Images();

	// the images starts after the configuration
	imageP = (void*) FLASH_BASE_ADR + sizeof(configParameter_s);

	// no Flex NVM EEPROM used, 4 kB RAM starting at 0x14000000
	// 802 bytes
	image_bufferP = (void*) FLEX_NVM_RAM_BASE;
}


/*
 ** ===================================================================
 **  Method      :  display_column
 */
/**
 *  @brief
 *  	Sets all LEDs for a column in the selected window on both sides.
 *  @param
 *      topFromBeginning		top surface starts from beginning
 *  @param
 *      win		UPPER or LOWER
 *  @param
 *      col		the column in the dot matrix
 */
/* ===================================================================*/
void display_column(bool topFromBeginning, windowT win, int col) {

	// clear last column
	if (displayMode[TOPSIDE][win] != BLANK) {
		if (displayMode[TOPSIDE][UPPER] == LIGHT) {
			set_ledColumn(TOPSIDE, front ? WHITE_COLUMN : RED_COLUMN);
			enable_bling[TOPSIDE] = FALSE;
			write_ledColumn(TOPSIDE);
			wait_ledColumn();
		} else {
			if (col >= display[TOPSIDE][win].length) {
				// window finished
				enable_bling[TOPSIDE] = TRUE;
			} else {
				enable_bling[TOPSIDE] = FALSE;
				if (topFromBeginning != right) {
					// != logical XOR
					set_ledColumn(TOPSIDE, display[TOPSIDE][win].dotmatrix[col]);
				} else {
					set_ledColumn(TOPSIDE, display[TOPSIDE][win].dotmatrix[display[TOPSIDE][win].length - col]);
				}
				write_ledColumn(TOPSIDE);
				wait_ledColumn();
			}
		}
	}

	if (displayMode[BOTTOMSIDE][win] != BLANK) {
		if (displayMode[TOPSIDE][UPPER] == LIGHT) {
			set_ledColumn(BOTTOMSIDE, front ? WHITE_COLUMN : RED_COLUMN);
			enable_bling[BOTTOMSIDE] = FALSE;
			write_ledColumn(BOTTOMSIDE);
			wait_ledColumn();
		} else {
			if (col >= display[BOTTOMSIDE][win].length) {
				// window finished
				enable_bling[BOTTOMSIDE] = TRUE;
			} else {
				enable_bling[BOTTOMSIDE] = FALSE;
				if (! (topFromBeginning != right)) {
					// != logical XOR
					set_ledColumn(BOTTOMSIDE, display[BOTTOMSIDE][win].dotmatrix[col]);
				} else {
					set_ledColumn(BOTTOMSIDE, display[BOTTOMSIDE][win].dotmatrix[display[BOTTOMSIDE][win].length - col]);
				}
				write_ledColumn(BOTTOMSIDE);
				wait_ledColumn();
			}
		}
	}
}


/*
 ** ===================================================================
 **  Method      :  display_blingColumn
 */
/**
 *  @brief
 *  	Sets all LEDs for a bling column on one side.
 *  @param
 *      sur		TOPSIDE/BOTTOMSIDE
 *  @param
 *      col		the column in the dot matrix
 */
/* ===================================================================*/
void display_blingColumn(surfaceT sur, int col) {
	if (sur == TOPSIDE) {
		if (!right) {
			// left side is default direction
			set_ledColumn(TOPSIDE, display[TOPSIDE][BLING].dotmatrix[col]);
		} else {
			set_ledColumn(TOPSIDE, display[TOPSIDE][BLING].dotmatrix[display[TOPSIDE][BLING].length-col]);
		}
		write_ledColumn(TOPSIDE);
	} else {
		if (!right) {
			// left side is default direction
			set_ledColumn(BOTTOMSIDE, display[BOTTOMSIDE][BLING].dotmatrix[display[BOTTOMSIDE][BLING].length-col]);
		} else {
			set_ledColumn(BOTTOMSIDE, display[BOTTOMSIDE][BLING].dotmatrix[col]);
		}
		write_ledColumn(BOTTOMSIDE);
	}
	wait_ledColumn();
}


/*
 ** ===================================================================
 **  Method      :  clear_display
 */
/**
 *  @brief
 *  	Sets all dots in the matrix to dark.
 *  @param
 *      sur		surface TOPSIDE or BOTTOMSIDE
 *  @param
 *      win		UPPER, LOWER, or BLING
 */
/* ===================================================================*/
void clear_display(surfaceT sur, windowT win) {

	memset(&display[sur][win].dotmatrix[0], 0, sizeof(display[sur][win].dotmatrix));
	display[sur][win].length = 0;
}


/*
 ** ===================================================================
 **  Method      :  put_str
 */
/**
 *  @brief
 *  	Puts a string to the display.
 *  	_      Space
 *  	\_     _
 *  	\\     \
 *  	\i<nn> image number 00..49
 *  	\f<nn> font         00..06
 *  	\c<nn> color 00..07
 *  	\s<nn> space in columns
 *  	\m<nn> cyclocomputer mode 00..09
 *  @param
 *      s			string
 *  @param
 *  	font		DOS5x12, DOS6x8, DOS7x12, DOS7x12b, DOS8x12, DOS12x16, DOS6x8t
 *  @param
 *      color		typeface color
 *  @param
 *      position	the column where the string start
 *  @param
 *      sur			surface TOPSIDE or BOTTOMSIDE
 *  @param
 *      win			UPPER, LOWER, or BLING
 *  @return
 *  	the next position (column)
 */
/* ===================================================================*/
int put_str(const char *s, fontT font, LED_colorT color, int position, surfaceT sur, windowT win) {
	int 	pos;         // current position (column) in dotmatrix
	LED_colorT col;
	fontT   fo;
	LED_nrT row;
	int 	column;
	char	c, c2;       // current character to display
	int		ci;          // character index
	uint16_t  char_pattern;
	uint64_t Set;
	uint16_t const *fontP;
	char number_s[4];
	uint8_t column_length, row_height;

	pos = position;
	col = color;
	fo  = font;

	for (ci = 0; ci < strlen(s); ci++) {
		/* next character */
		switch (fo) {
		case DOS5x12:
			column_length = 5;
			row_height = 12;
			fontP = &font_5x12[0][0];
			break;
		case DOS6x8t:
			// fall through
		case DOS6x8:
			column_length = 6;
			row_height = 8;
			fontP = &font_6x8[0][0];
			break;
		case DOS7x12:
			column_length = 7;
			row_height = 12;
			fontP = &font_7x12[0][0];
			break;
		case DOS7x12b:
			column_length = 7;
			row_height = 12;
			fontP = &font_7x12b[0][0];
			break;
		case DOS8x12:
			column_length = 8;
			row_height = 12;
			fontP = &font_8x12[0][0];
			break;
		case DOS12x16:
			column_length = 12;
			row_height = 16;
			fontP = &font_12x16[0][0];
			break;
		default:
			column_length = 7;
			row_height = 12;
			fontP = &font_7x12[0][0];
			break;
		}

		c = s[ci];

		if (c == '_') {
			c = ' ';
		} else if (c == '\\') {
			// escape character
			switch (s[++ci]) {
			case '_':
				c = '_';
				break;
			case '\\':
				c = '\\';
				break;
			case 'i':
				// insert image
				strncpy(number_s, s+ci+1, 2);
				pos = put_Image(atoi(number_s), pos, sur, win);
				ci = ci+2;
				continue;
			case 'c':
				// change color
				strncpy(number_s, s+ci+1, 2);
				col = atoi(number_s);
				ci = ci+2;
				continue;
			case 'f':
				// change font
				strncpy(number_s, s+ci+1, 2);
				fo = atoi(number_s);
				ci = ci+2;
				continue;
			case 's':
				// insert spaces (columns)
				strncpy(number_s, s+ci+1, 2);
				ci = ci+2;
				pos = pos + atoi(number_s);;
				continue;
			default:
				// eat backslash
				c = s[ci];
			}
		} else if (c == '\303') {
			// UTF-8
			c2 = s[++ci];
			switch (c2) {
			case '\244':
				// ä
				c = '\204';
				break;
			case '\266':
				// ö
				c = '\224';
				break;
			case '\274':
				// ü
				c = '\201';
				break;
			default:
				//
				c = s[--ci];
			}
		}

		for (column=0; column < column_length; column++) {
			/* next column */
			if (pos >= MAX_COLUMN) {
				/* overflow, string is to long */
				display[sur][win].length = pos;
				return pos;
			}
			display[sur][win].dotmatrix[pos] = 0;
			uint8_t cint = c;
			char_pattern = *(fontP + cint * column_length + column);
			for (row=0; row < row_height; row++) {
				/* next row */
				if (char_pattern & (0x01 << row)) {
					if (win == LOWER) {
						Set  = (uint64_t)col << (3 * (16-row));
						if (fo == DOS6x8t) {
							// upper line
							Set = Set >> 24;
						}
					} else {
						Set  = (uint64_t)col << (3 * row);
						if (fo == DOS6x8t) {
							// upper line
							Set = Set << 24;
						}
					}
					display[sur][win].dotmatrix[pos] = display[sur][win].dotmatrix[pos] | Set;
				}
			}
			pos++;
		}
	}
	display[sur][win].length = pos;
	return pos;
}


/*
 ** ===================================================================
 **  Method      :  put_heart
 */
/**
 *  @brief
 *  	Puts a heart in the display. The character is 16x16
 *  @param
 *      position	the column where the string start
 *  @param
 *      color		forground color
 *  @param
 *      sur			surface TOPSIDE or BOTTOMSIDE
 *  @param
 *      win			UPPER, LOWER, or BLING
 *  @return
 *  	the next position (column)
 */
/* ===================================================================*/
int put_heart(int position, const LED_colorT color, surfaceT sur, windowT win) {
	int 	pos;         // current position (column) in dotmatrix
	int 	column;


	pos = position;
	for (column=0; column < 16; column++) {
		if (pos >= MAX_COLUMN) {
			/* overflow, image is to long */
			return pos;
		}
		if (win == LOWER) {
			display[sur][win].dotmatrix[pos]  = heart_pattern_r[column] * color;
		} else {
			display[sur][win].dotmatrix[pos]  = heart_pattern[column] * color;
		}
		pos++;
	}
	display[sur][win].length = pos;
	return pos;
}

/*
 ** ===================================================================
 **  Method      :  put_Swisscross
 */
/**
 *  @brief
 *  	Puts a Swisscross in the display. The character is 12x12.
 *  	Change to 16x16!
 *  @param
 *      position	the column where the string start
  *  @param
 *      sur			surface TOPSIDE or BOTTOMSIDE
 *  @param
 *      win			UPPER, LOWER, or BLING
 *  @return
 *  	the next position (column)
 */
/* ===================================================================*/
int put_Swisscross(int position, surfaceT sur, windowT win) {
	int 	pos;         // current position (column) in dotmatrix
	int 	column;

	pos = position;
	for (column=0; column < 16; column++) {
		/* next column (there are 12 columns) */
		if (pos >= MAX_COLUMN) {
			/* overflow, string is to long */
			return pos;
		}
		display[sur][win].dotmatrix[pos]  = swiss_pattern[column];
		pos++;
	}
	display[sur][win].length = pos;
	return pos;
}

/*
 ** ===================================================================
 **  Method      :  put_Snow
 */
/**
 *  @brief
 *  	Puts snow in the display. The character is 16x16.
 *  @param
 *      position	the column where the string start
  *  @param
 *      sur			surface TOPSIDE or BOTTOMSIDE
 *  @param
 *      win			UPPER, LOWER, or BLING
 *  @return
 *  	the next position (column)
 */
/* ===================================================================*/
int put_Snow(int position, surfaceT sur, windowT win) {
	int 	pos;         // current position (column) in dotmatrix
	int 	column;

	pos = position;
	for (column=0; column < 16; column++) {
		if (pos >= MAX_COLUMN) {
			/* overflow, string is to long */
			return pos;
		}
		display[sur][win].dotmatrix[pos]  = snow_pattern[column];
		pos++;
	}
	display[sur][win].length = pos;
	return pos;
}

/*
 ** ===================================================================
 **  Method      :  put_Tricolore
 */
/**
 *  @brief
 *  	Puts a Tricolore in the display. The character is 20x14.
 *  	Change to 24x16!
 *  @param
 *      position	the column where the tricolore starts
 *  @param
 *      sur			surface TOPSIDE or BOTTOMSIDE
 *  @param
 *      win			UPPER, LOWER, or BLING
 *  @param
 *  	color		the 3 colors (left to right, UPPER to LOWER)
 *  @param
 *  	vertical	vertical lanes (stripes)
 *  @param
 *  	frame		w/ or w/o frame
 *  @return
 *  	the next position (column)
 */
/* ===================================================================*/
int put_Tricolore(int position, surfaceT sur, windowT win, const LED_colorT color[3], const bool vertical, const bool frame) {
	int 	pos;         // current position (column) in dotmatrix
	LED_nrT row;
	int 	column;
	int     lane;
	uint64_t Set = 0;

	pos = position + 1;
	if (vertical) {
		// vertical
		for (lane = 0; lane < 3; lane++) {
			for (column=0; column < 6; column++) {
				/* next column  */
				if (pos >= MAX_COLUMN) {
					/* overflow, string is to long */
					display[sur][win].length = pos;
					return pos;
				}
				Set = 0;
				for (row=1; row < 13; row++) {
					/* next row  */
					if (win == LOWER) {
						Set  = Set | (uint64_t)color[lane] << (3 * (15-row));
					} else {
						Set  = Set | (uint64_t)color[lane] << (3 * row);
					}
				}
				display[sur][win].dotmatrix[pos] = Set;
				pos++;
			}
		}
	} else {
		// horizontal
		for (lane = 0; lane < 3; lane++) {
			for (row=0; row < 4; row++) {
				/* next row */
				if (win == LOWER) {
					Set  = Set | (uint64_t)color[lane] << (3 * (15 - row - lane*4 - 1));
				} else {
					Set  = Set | (uint64_t)color[lane] << (3 * (row + lane*4 + 1));
				}
			}
		}
		for (column=1; column < 19; column++) {
			if (pos >= MAX_COLUMN) {
				/* overflow, string is to long */
				display[sur][win].length = pos;
				return pos;
			}
			display[sur][win].dotmatrix[pos++] = Set;
		}
	}

	if (frame) {
		if (win == LOWER) {
			display[sur][win].dotmatrix[position]    = 07777777777777700;
			display[sur][win].dotmatrix[position+19] = 07777777777777700;
		} else {
			display[sur][win].dotmatrix[position]    =   077777777777777;
			display[sur][win].dotmatrix[position+19] =   077777777777777;
		}
		pos = position+1;
		for (column=1; column < 19; column++) {
			if (win == LOWER) {
				Set = 07000000000000700;
			} else {
				Set = 070000000000007;
			}
			display[sur][win].dotmatrix[pos] = display[sur][win].dotmatrix[pos] | Set;
			pos++;
		}
	}

	display[sur][win].length = pos;
	return ++pos;
}

 /*
 ** ===================================================================
 **  Method      :  put_Meander
 */
/**
 *  @brief
 *  	Puts a Meander in the display. The character is 8x11 pixel.
 *  @param
 *      position	the column where the string start
 *  @param
 *      front_color	foreground (front) color
 *  @param
 *      back_color	background color
 *  @param
 *      sur			surface TOPSIDE or BOTTOMSIDE
 *  @param
 *      win			UPPER, LOWER, or BLING
 *  @return
 *  	the next position (column)
 */
/* ===================================================================*/
int put_Meander(int position, const LED_colorT front_color, const LED_colorT back_color, surfaceT sur, windowT win) {
	int 	pos;         // current position (column) in dotmatrix
	int 	column;

	pos = position;
	for (column=0; column < 8; column++) {
		if (pos >= MAX_COLUMN) {
			/* overflow, string is to long */
			return pos;
		}
		display[sur][win].dotmatrix[pos]  = (meander_pattern[column] * front_color) |
											((~(meander_pattern[column]) & 01111111111100000) * back_color);
		pos++;
	}
	display[sur][win].length = pos;
	return pos;
}

/*
** ===================================================================
**  Method      :  put_Square
*/
/**
*  @brief
*  	Puts a square in the display. The character is 8x11 pixel.
*  @param
*      position	the column where the string start
*  @param
*      front_color	foreground (front) color
*  @param
*      side			side length (max. 16)
*  @param
*  	   shift		shift from bottom
*  @param
*      sur			surface TOPSIDE or BOTTOMSIDE
*  @param
*      win			UPPER, LOWER, or BLING
*  @return
*  	the next position (column)
*/
/* ===================================================================*/
int put_Square(int position, const LED_colorT front_color, const uint8_t side, const uint8_t shift, surfaceT sur, windowT win) {
	int 	pos;         // current position (column) in dotmatrix
	int 	column;

	pos = position;
	for (column=0; column < side; column++) {
		if (pos >= MAX_COLUMN) {
			/* overflow, string is to long */
			return pos;
		}
		display[sur][win].dotmatrix[pos]  = ((01111111111111111 >> (3*(16-side))) * front_color) << (3*shift);
		pos++;
	}
	display[sur][win].length = pos;
	return pos;
}



/*
 ** ===================================================================
 **  Method      :  save_Image
 */
/**
 *  @brief
 *  	Saves a image from the image_buffer into the flash
 *  @param
 *      number		image number
 */
/* ===================================================================*/

void save_Image(int number) {

	char str[40];

	if (FlashMem_SetBlockFlash(
			(FlashMem_TDataAddress) image_bufferP,
			(FlashMem_TAddress) &(*imageP)[number],
			sizeof(image_s))
			!= ERR_OK) {
		strcpy(str, "\nError: cannot save image into FLASH\n");
		usb_puts(str);
	}
}

/*
 ** ===================================================================
 **  Method      :  put_Image
 */
/**
 *  @brief
 *  	Gets an image from the flash and writes to a window
 *  @param
 *      number		image numer
 *  @param
 *  	position    the column where the image starts
 *  @param
 *  	sur			surface
 *  @param
 *  	win			window
 *  @return
 *  	new position
 */
/* ===================================================================*/

int put_Image(int number, int position, surfaceT sur, windowT win) {

	int pos = position;
	int length = (*imageP)[number].length;
	uint64_t col;
	uint8_t i, row;

	if (length > MAX_COLUMN) {
		return position;
	}

	for (i=0; i<length; i++) {
		if (win == LOWER) {
			// reverse the the rows (row 0 -> row 15)
			col = (*imageP)[number].dotmatrix[i];
			display[sur][win].dotmatrix[pos] = col & 07;
			for (row=0; row < 15; row++) {
				col = col >> 3;
				display[sur][win].dotmatrix[pos] = display[sur][win].dotmatrix[pos] << 3;
				display[sur][win].dotmatrix[pos] = display[sur][win].dotmatrix[pos] | (col & 07);
			}
		} else {
			display[sur][win].dotmatrix[pos] = (*imageP)[number].dotmatrix[i];
		}
		pos++;
	}

	display[sur][win].length = pos;
	return pos;
}

/*
 ** ===================================================================
 **  Method      :  images_Init
 */
/**
 *  @brief
 *  	Saves some default images into the flash
 */
/* ===================================================================*/

void images_Init() {
	int position;

	// 0: switzerland
	clear_display(TOPSIDE, BLING);
	position = put_Swisscross(0, TOPSIDE, BLING);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(0);

	// 1: germany
	clear_display(TOPSIDE, BLING);
	position = put_Tricolore(0, TOPSIDE, BLING, Germany, FALSE, TRUE);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(1);

	// 2: austria
	clear_display(TOPSIDE, BLING);
	position = put_Tricolore(0, TOPSIDE, BLING, Austria, FALSE, TRUE);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(2);

	// 3: italy
	clear_display(TOPSIDE, BLING);
	position = put_Tricolore(0, TOPSIDE, BLING, Italy, TRUE, TRUE);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(3);

	// 4: france
	clear_display(TOPSIDE, BLING);
	position = put_Tricolore(0, TOPSIDE, BLING, France, TRUE, TRUE);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(4);

	// 5: belgium
	clear_display(TOPSIDE, BLING);
	position = put_Tricolore(0, TOPSIDE, BLING, Belgium, TRUE, TRUE);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(5);

	// 6: spain
	clear_display(TOPSIDE, BLING);
	position = put_Tricolore(0, TOPSIDE, BLING, Spain, FALSE, TRUE);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(6);

	// 10: heart
	clear_display(TOPSIDE, BLING);
	position = put_heart(0, RED, TOPSIDE, BLING);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(10);

	// 11: snow
	clear_display(TOPSIDE, BLING);
	position = put_Snow(0, TOPSIDE, BLING);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(11);

	// 12: meander yellow
	clear_display(TOPSIDE, BLING);
	position = put_Meander(0, YELLOW, BLACK, TOPSIDE, BLING);
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(12);

	// 13: meander green red
	clear_display(TOPSIDE, BLING);
	position = put_Meander(0, GREEN, RED, TOPSIDE, BLING);
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(13);

	// 15: ParisBrestParis
	clear_display(TOPSIDE, BLING);
	position = put_str("Paris\\c07Brest\\c01Paris", DOS5x12, BLUE, 1, TOPSIDE, BLING);
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(15);

	// 20: germany spyr.ch swisscross
	clear_display(TOPSIDE, BLING);
	position = put_Image(2, 0, TOPSIDE, BLING); // Austria
	position = put_str("spyr.ch", DOS7x12, GREEN, position, TOPSIDE, BLING);
	position = put_Image(0, position+2, TOPSIDE, BLING); // Switzerland
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(20);

	// 21: countries
	clear_display(TOPSIDE, BLING);
	position = put_Image(2, 0, TOPSIDE, BLING); // Austria
	position = put_Image(3, position, TOPSIDE, BLING); // Italy
	position = put_Image(4, position, TOPSIDE, BLING); // France
	position = put_Image(5, position, TOPSIDE, BLING); // Belgium
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(21);

	// 22: countries
	clear_display(TOPSIDE, BLING);
	position = put_Image(0, 0, TOPSIDE, BLING); // Switzerland
	position = put_Image(3, position, TOPSIDE, BLING); // Italy
	position = put_Image(4, position, TOPSIDE, BLING); // France
	position = put_Image(1, position, TOPSIDE, BLING); // Germany
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(22);

	// 23: countries
	clear_display(TOPSIDE, BLING);
	position = put_Image(1, 0, TOPSIDE, BLING); // Germany
	position = put_Image(0, position, TOPSIDE, BLING); // Switzerland
	position = put_Image(3, position, TOPSIDE, BLING); // Italy
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(23);

	// 24: veloblingbling
	clear_display(TOPSIDE, BLING);
	position = put_str("velo\\c07bling\\c01bling", DOS7x12b, BLUE, 1, TOPSIDE, BLING);
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(24);

	// 25: Geberit String
	clear_display(TOPSIDE, BLING);
	position = put_Square(10, BLUE, 10, 2, TOPSIDE, BLING);
	position = put_str("GEBERIT", DOS8x12, WHITE, position+3, TOPSIDE, BLING);
	image_bufferP->length = position;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(25);

	// 26: Geberit Logo
	clear_display(TOPSIDE, BLING);
	position = put_Square(0, BLUE, 10, 2, TOPSIDE, BLING);
	image_bufferP->length = position + 6;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(26);

	// 27: Geberit I Love Water
	clear_display(TOPSIDE, BLING);
	position = put_str("I", DOS8x12, WHITE, 10, TOPSIDE, BLING);
	position = put_heart(position+2, YELLOW, TOPSIDE, BLING);
	position = put_str("Water", DOS8x12, WHITE, position+3, TOPSIDE, BLING);
	image_bufferP->length = position + 2;
	memcpy(&image_bufferP->dotmatrix, &display[TOPSIDE][BLING].dotmatrix, sizeof(image_bufferP->dotmatrix));
	save_Image(27);

//	while (FlashMem_Busy(NULL)) {
//		// busy wait
//		;
//	}
}


/**
 ** @}
 */
