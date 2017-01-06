/**
 *  @brief
 *  	Write strings to the dot matrix and display columns.
 *  	
 *      The character height is 12 pixel (already prepared for 16 pixel)  
 *      There are 64 columns:   
 *      There are 100 (64) columns:   
 *        20 chars in 5x12 font, 
 *        14 chars in 7x12 font, 
 *        12 chars in 8x12 font, 
 *        8  chars in 12x16 font
 *      
 *  @file
 *      display.h
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


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "led.h"
#include "PE_Types.h"

#define MAX_COLUMN	100
#define MAX_ROW		16
#define MAX_IMAGE	50

typedef enum {CYCLOCOMPUTER, STRING, IMAGE, LIGHT, BLANK} Display_modeT;
typedef enum {UPPER, LOWER, BLING} windowT;
typedef enum {DOS5x12, DOS6x8, DOS7x12, DOS7x12b, DOS8x12, DOS12x16} fontT;

typedef struct image_s {
	uint16_t length;
	uint64_t dotmatrix[MAX_COLUMN];
} image_s;

extern image_s (*imageP)[];
extern image_s *image_bufferP;

extern image_s display[BOTTOMSIDE+1][BLING+1];


/*
 ** ===================================================================
 **  Method      :  display_Init
 */
/**
 *  @brief
 *  	Initialises the display.
 */
/* ===================================================================*/
void display_Init();

/*
 ** ===================================================================
 **  Method      :  display_column
 */
/**
 *  @brief
 *  	Sets all LEDs for a column in the selected window on both sides.
 *  @param
 *      win		UPPER or LOWER
 *  @param
 *      col		the column in the dot matrix  	
 */
/* ===================================================================*/
void display_column(windowT win, int col);

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
void display_blingColumn(surfaceT sur, int col);

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
void clear_display(surfaceT sur, windowT win);

/*
 ** ===================================================================
 **  Method      :  put_str
 */
/**
 *  @brief
 *  	Puts a string to the dotmatrix. 
 *  	_      Space
 *  	\_     _
 *  	\\     \
 *  	\i<nn> image number 00..49
 *  	\f<nn> font         00..04
 *  	\c<nn> color 00..07 
 *  	\m<nn> cyclocomputer mode 00..09
 *  	\ch \de \fr \at \it ...
 *  @param
 *      s			string  	
 *  @param
 *  	font		DOS5x12, DOS7x12, DOS8x12, DOS12x16
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
int put_str(const char *s, fontT font, LED_colorT color, int position, surfaceT sur, windowT win);

/*
 ** ===================================================================
 **  Method      :  put_heart
 */
/**
 *  @brief
 *  	Puts a heart in the dotmatrix. The character is 12x12. 
 *  	Change to 16x16!
 *  @param
 *      color_base	base color e.g. yellow
 *  @param
 *  	color_aa	anti aliasing e.g. red     	
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
int put_heart(int position, const LED_colorT color, surfaceT sur, windowT win);

/*
 ** ===================================================================
 **  Method      :  put_Swisscross
 */
/**
 *  @brief
 *  	Puts a Swisscross in the dotmatrix. The character is 12x12. 
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
int put_Swisscross(int position, surfaceT sur, windowT win);

/*
 ** ===================================================================
 **  Method      :  put_Tricolore
 */
/**
 *  @brief
 *  	Puts a Tricolore in the dotmatrix. The character is 18x12. 
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
int put_Tricolore(int position, surfaceT sur, windowT win, const LED_colorT color[3], const bool vertical, const bool frame) ;

/*
 ** ===================================================================
 **  Method      :  save_Image
 */
/**
 *  @brief
 *  	Saves a image from the image buffer into the flash
 *  @param
 *      number		image numer 
 */
/* ===================================================================*/

void save_Image(int number);

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
 *  @retunr
 *  	new position
 */
/* ===================================================================*/

int put_Image(int number, int position, surfaceT sur, windowT win);

/*
 ** ===================================================================
 **  Method      :  images_Init
 */
/**
 *  @brief
 *  	Saves some default images into the flash
 *  @param
 *      number		image numer 
 */
/* ===================================================================*/

void images_Init();

#endif /* DISPLAY_H_ */
