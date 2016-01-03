/**
 *  @brief
 *      Very simple script interpreter. Every line will be interpreted by
 *      CLI except lines beginning with : (colon) or ; (semicolon). After
 *      reading a semicolon the script restarts from the beginning.
 *      A line has to <= 80 chars long.
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
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2016-01-02
 *  @remark
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 *  @version
 *      Version 3.7, 2015/08/11
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


// Global Variables
// ****************
int currScript = 40;
bool scriptExecution = FALSE;
bool script_set = FALSE;

// Local Variables
// ***************
char *charP;
uint8_t waitTime = 0;



/*
 ** ===================================================================
 **  Method      :  script_Interpreter
 */
/**
 *  @brief
 *      Very simple script interpreter. Every line will be interpreted by
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
				scriptExecution = FALSE;
				break;
			}

			if (line[0] == semicolon_c) {
				// script finished, restart from the beginning
				waitTime = 0;
				charP = (char*) &(*imageP)[currScript].dotmatrix[0];
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
 **  Method      :  script_Start
 */
/**
 *  @brief
 *  	Starts the script execution.
 *
 *  @param
 *  	number	image number in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Start(char* number, channelT ch) {

	currScript = atoi(number);
	charP = (char*) &(*imageP)[currScript].dotmatrix[0];
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
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Stop(channelT ch) {

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
	uint8_t i;

	currScript = atoi(number);
	charP = (char*) &(*imageP)[currScript].dotmatrix[0];

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
			charP = (char*) &(*imageP)[currScript].dotmatrix[0];
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
 *  	number	image number in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Set(char* number, channelT ch) {

	script_set = TRUE;
	currScript = atoi(number);
	charP = (char*) &image_bufferP->dotmatrix[0];
}


/*
 ** ===================================================================
 **  Method      :  script_Line
 */
/**
 *  @brief
 *  	saves one script line
 *
 *  @param
 *  	line	script line in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Line(char* line, channelT ch) {

	// save line
	strcpy(charP, line);
	charP = charP + strlen(line);
	*charP++ = A_LF;

	if (line[0] == semicolon_c) {
		script_set = FALSE;
		// save buffer to flash
		image_bufferP->length = 0;
		save_Image(currScript);
	}

	if (charP > (char*) image_bufferP + sizeof(image_s)) {
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

