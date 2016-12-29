/**
 *  @brief
 *      Very simple script interpreter. Every line is interpreted by
 *      CLI except lines beginning with : (colon) or ; (semicolon). After
 *      reading a semicolon the script restarts from the beginning.
 *      A line has to be <= 80 chars long.
 *
 *      The script buffer is 800 bytes and shares the same memory for the
 *      images (dotmatrix). That means one buffer has room for about 50
 *      command lines. If that is not enough then you can start another
 *      script buffer within the script.
 *
 *      image_bufferP (see module display) is also as RAM buffer used.
 *
 *      :wait n
 *      waits n seconds
 *
 *		:exit
 *		aborts script
 *
 *      > set script 40
 *      set string upper Hallo
 *      set string lower Velo
 *      set upper string
 *      set lower string
 *      :wait 10
 *      set upper speed
 *      set lower trip
 *      :wait 10
 *      ;
 *
 *		> show script 40
 *
 *      > script start 40
 *      > script stop
 *
 *      > script test 40
 *
 *  @file
 *      script.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2016-01-02
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
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

// PE include files
// ****************

// application include files
// *************************
#include "definitions.h"
#include "cli.h"
#include "visual/display.h"
#include "comm/usb.h"
#include "mode.h"
#include "driver/parameter.h"

// command tokens
// **************
static const char wait_s[]   = ":wait";
static const char w_s[]      = ":w";
static const char exit_s[]   = ":exit";
static const char e_s[]      = ":e";

static const char colon_c  = ':';
static const char semicolon_c  = ';';

// Sample scripts
// don't forget to escape the \ (\\) and the special chars

// Geberit AquaClean
static const char geberitScript[] =
		"set up blk\n"
		"set lo blk\n"
		"set bling blk\n"
		":w 5\n"
		"set col up w\n"
		"set img up 25\n"
		"set col lo m\n"
		"set str lo \\f04_AquaClean\n"
		"set up img\n"
		"set lo string\n"
		"set bling blk\n"
		":w 6\n"
		"set img bling 26\n"
		"set up blk\n"
		"set lo blk\n"
		"set bling img\n"
		":w 3\n"
		"set col up g\n"
		"set str up \\f03__Karl_Zahner\n"
		"set img lo 27\n"
		"set up string\n"
		"set lo img\n"
		"set bling blk\n"
		":w 3\n"
		"set str up \\f00__Andreas_Helbling\n"
		":w 3\n"
		"set str up \\f03_Margit_Harsch\n"
		":w 3\n"
		"set str up \\f00__Marc_Attenhofer\n"
		":w 3\n"
		"set str up \\f00__Martin_Baum\201ller\n"
		":w 3\n"
		"set str up \\f00__Hubert_Britschgi\n"
		":w 3\n"
		"set img lo 24\n"
		"set img bling 0\n"
		"set up speed\n"
		"set lo img\n"
		"set bling img\n"
		":w 8\n"
		";\n";



// Global Variables
// ****************
int currScript = 30;
bool scriptExecution = FALSE;
bool script_set = FALSE;

// Local Variables
// ***************
char *charInterpreterP;		// points to the flash image buffer for interpreter
char *charBufferP;			// points to the image buffer
int scriptSetNumber;
uint8_t waitTime = 0;

/*
 ** ===================================================================
 **  Method      :  script_Init
 */
/**
 *  @brief
 *      Initializes sample scripts
 *
 */
/* ===================================================================*/
void script_Init(void) {
	char *chP;			// points to the image buffer

	// Geberit script to 30
	chP = (char*) &image_bufferP->dotmatrix[0];
	strcpy(chP, geberitScript);
	// save buffer to flash
	image_bufferP->length = 0;
	save_Image(30);
}


/*
 ** ===================================================================
 **  Method      :  script_Interpreter
 */
/**
 *  @brief
 *      Very simple script interpreter. Every line is interpreted by
 *      CLI except lines beginning with : (colon) or ; (semicolon). After
 *      reading a semicolon the script restarts from the beginning.
 *
 *      The script buffer is 800 bytes and shares the same memory for the
 *      images (dotmatrix). That means one buffer has room for about 50
 *      command lines.
 *      If that is not enough then you can start another script buffer.
 *
 *  	Called every second by watch_Synch (not called as long as USB is
 *  	active)
 *
 */
/* ===================================================================*/
void script_Interpreter(void) {
	char line[81];
	char *token;
	uint8_t i;

	if (waitTime > 0) {
		waitTime--;
	} else {
		while (TRUE) {
			// get line from buffer
			for (i=0; i<80; i++) {
				if (*charInterpreterP == A_LF) {
					line[i] = '\0';
					charInterpreterP++;
					break;
				} else {
					line[i] = *charInterpreterP++;
				}
			}
			if (i == 80) {
				// no end of line -> abort
				scriptExecution = FALSE;
				break;
			}

			if (line[0] == semicolon_c) {
				// script finished, restart from the beginning
				waitTime = 0;
				charInterpreterP = (char*) &(*imageP)[currScript].dotmatrix[0];
				break;
			} else if(line[0] == colon_c) {
				// special commands
				// tokenize
				token = strtok(line, " ");
				if (! strcmp(token, wait_s) || ! strcmp(token, w_s)) {
					token = strtok(NULL, " ");
					waitTime = atoi(token);
					break;
				} else if (! strcmp(token, exit_s) || ! strcmp(token, e_s)) {
					scriptExecution = FALSE;
					break;
				} else {
					// unknown special command
					scriptExecution = FALSE;
					break;
				}
			} else {
				// interpret command line
				(void) cli_parse(line, SCRIPT_CHANNEL);
			}
		}
	}
}

/*
 ** ===================================================================
 **  Method      :  script_Reset
 */
/**
 *  @brief
 *  	Sets the script pointer to the beginning.
 *
 *  @param
 *  	number	image number in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Reset() {
	charInterpreterP = (char*) &(*imageP)[currScript].dotmatrix[0];
}


/*
 ** ===================================================================
 **  Method      :  script_Start
 */
/**
 *  @brief
 *  	Starts the script execution.
 *
 *  @param
 *  	number	image number in ascii
 *
 */
/* ===================================================================*/
void script_Start(char* number) {

	currScript = atoi(number);
	charInterpreterP = (char*) &(*imageP)[currScript].dotmatrix[0];
	scriptExecution = TRUE;
}

/*
 ** ===================================================================
 **  Method      :  script_Stop
 */
/**
 *  @brief
 *  	Stops the script execution.
 *
 *  @param
 *  	none
 *
 */
/* ===================================================================*/
void script_Stop() {

	scriptExecution = FALSE;
}

/*
 ** ===================================================================
 **  Method      :  script_Test
 */
/**
 *  @brief
 *  	Very similar to script_Interpreter but ignores :wait and aborts
 *  	after ;. It shows the commands and their responses.
 *
 *  @param
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Test(char* number, channelT ch) {
	char line[81];
	char *token;
	char *charP;			// points to the flash image buffer
	uint8_t i;

	int scriptNumber = atoi(number);
	charP = (char*) &(*imageP)[scriptNumber].dotmatrix[0];

	while (TRUE) {
		// get line from buffer
		for (i=0; i<80; i++) {
			if (*charP == A_LF) {
				line[i] = '\0';
				charP++;
				break;
			} else {
				line[i] = *charP++;
			}
		}
		if (i == 80) {
			// no end of line -> abort
			puts_ch("no end of line -> abort\n", ch);
			scriptExecution = FALSE;
			break;
		}

		puts_ch("script> ", ch);
		puts_ch(line, ch);
		puts_ch("\n", ch);

		if (line[0] == semicolon_c) {
			// script finished
			puts_ch("script finished\n", ch);
			waitTime = 0;
			charP = (char*) &(*imageP)[scriptNumber].dotmatrix[0];
			break;
		} else if(line[0] == colon_c) {
			// special commands
			// tokenize
			token = strtok(line, " ");
			if (! strcmp(token, wait_s) || ! strcmp(token, w_s)) {
				token = strtok(NULL, " ");
				waitTime = atoi(token);
				puts_ch("wait ignored\n", ch);
				// no break;
			} else if (! strcmp(token, exit_s) || ! strcmp(token, e_s)) {
				scriptExecution = FALSE;
				puts_ch("script finished\n", ch);
				break;
			} else {
				// unknown special command
				scriptExecution = FALSE;
				puts_ch("unknown special command -> script aborted\n", ch);
				break;
			}
		} else {
			// interpret command line
			(void) cli_parse(line, ch);
		}
	}
}


/*
 ** ===================================================================
 **  Method      :  script_Set
 */
/**
 *  @brief
 *  	set the contents of a script
 *
 *  @param
 *  	none
 *
 */
/* ===================================================================*/
void script_Set(char* number) {

	scriptSetNumber = atoi(number);
	script_set = TRUE;
	charBufferP = (char*) &image_bufferP->dotmatrix[0];
}


/*
 ** ===================================================================
 **  Method      :  script_Line
 */
/**
 *  @brief
 *  	Writes one script line to the image_buffer,
 *  	after the last line save the buffer to the flash.
 *
 *  @param
 *  	line	script line in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Line(char* line, channelT ch) {

	// write line
	strcpy(charBufferP, line);
	charBufferP = charBufferP + strlen(line);
	*charBufferP++ = A_LF;

	if (line[0] == semicolon_c) {
		script_set = FALSE;
		// save buffer to flash
		image_bufferP->length = 0;
		save_Image(scriptSetNumber);
	}

	if (charBufferP > (char*) image_bufferP + sizeof(image_s)) {
		// buffer overflow
		script_set = FALSE;
		puts_ch("buffer overflow\n", ch);
	}
}


/*
 ** ===================================================================
 **  Method      :  script_Show
 */
/**
 *  @brief
 *  	shows the contents of a script
 *
 *  @param
 *  	number	script line in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Show(char* number, channelT ch) {
	char line[81];
	uint8_t i;
	char *charP;			// points to the flash image buffer

	int scriptNumber = atoi(number);
	charP = (char*) &(*imageP)[scriptNumber].dotmatrix[0];

	while (TRUE) {
		// get line from buffer
		for (i=0; i<80; i++) {
			if (*charP == A_LF) {
				line[i] = '\0';
				charP++;
				break;
			} else {
				line[i] = *charP++;
			}
			if (charP > (char*) &(*imageP)[scriptNumber].dotmatrix[0] + sizeof(image_s)) {
				// buffer overflow
				puts_ch("buffer overflow\n", ch);
				return;
			}
		}

		puts_ch(line, ch);
		puts_ch("\n", ch);

		if (line[0] == semicolon_c) {
			// script finished
			break;
		}


	}
}

