/**
 *  @brief
 *      Set the mode by using the button
 *      
 *  @file
 *      mode.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-20
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
#include "math.h"

// PE include files
// ****************
#include "Cpu.h"
#include "RTC1.h"

// application include files
// *************************
#include "definitions.h"
#include "visual/led.h"
#include "visual/display.h"
#include "powermgr.h"
#include "button.h"
#include "comm/usb.h"
#include "cyclo/cyclocomputer.h"
#include "cyclo/watch.h"
#include "motion/wheelsensor.h"
#include "motion/bling.h"
#include "driver/parameter.h"
#include "hmi/cli.h"

#define MODE_STEPS 12
#define COLOR_STEPS 7

struct mode_step_s {
	LED_nrT        nr; 
	Display_modeT  display_mode;
	Cyclo_modeT    cyclo_mode;
};

const static const struct mode_step_s mode_step[MODE_STEPS] = {
		{LED1,  CYCLOCOMPUTER, CURRENTSPEED},		// 0
		{LED2,  CYCLOCOMPUTER, TRIPDISTANCE},		// 1
		{LED3,  CYCLOCOMPUTER, TOTALDISTANCE},		// 2
		{LED4,  CYCLOCOMPUTER, CURRENTALTITUDE},	// 3
		{LED5,  CYCLOCOMPUTER, TRIPELEVATIONGAIN},	// 4
		{LED6,  CYCLOCOMPUTER, CURRENTTIME},		// 5
		{LED7,  CYCLOCOMPUTER, TRIPTIME},			// 6
		{LED8,  CYCLOCOMPUTER, CHRONOTIME},			// 7
		{LED9,  STRING,        NOCYCLO},			// 8
		{LED10, IMAGE,         NOCYCLO},			// 9
		{LED11, BLANK,         NOCYCLO},			// 10
		{LED12, BLANK,         NOCYCLO}				// 11
};


// Global Variables
// ****************
Display_modeT displayMode[BOTTOMSIDE+1][BLING+1] = 
	{{CYCLOCOMPUTER, IMAGE, BLANK}, {CYCLOCOMPUTER, IMAGE, BLANK}};

Cyclo_modeT cycloMode[BOTTOMSIDE+1][BLING+1] = 
	{{CURRENTSPEED, TRIPDISTANCE, CURRENTSPEED}, {CURRENTSPEED, TRIPDISTANCE, CURRENTSPEED}};

char displayString[BOTTOMSIDE+1][BLING+1][40] = 
	{{"GNU/Linux", "spyr.ch", "spyr.ch"}, {"GNU/Linux", "spyr.ch", "spyr.ch"}};
//	{{"  & ein gutes", "neues Jahr!", "spyr.ch"}, {"& ein gutes", "neues Jahr!", "spyr.ch"}};

LED_colorT displayColor[BOTTOMSIDE+1][BLING+1] = 
	{{GREEN, RED, RED}, {GREEN, RED, RED}};

int displayImage[BOTTOMSIDE+1][BLING+1] = 
	{{20, 24, 0}, {20, 24, 0}};

bool imperialUnits = FALSE;											/**< display variables in imperial units */
surfaceT surface = TOPSIDE;

// Local Variables
// ***************
static int currModeStep[BLING+1] = {0, 1, 11};


/*
** ===================================================================
**  Method      :  set_Mode
*/
/**
 *  @brief
 *  	Select modes width button.
 *  	Called by operation if button pressed
 */
/* ===================================================================*/
void set_Mode() {
	windowT win;

	operating_mode = MODE_BUTTON;
	clear_leds(TOPSIDE);



	// button pressed
	while (! ButtonReleased) {
		// wait till button released
		wait_10ms(2);
	}

	if (ButtonLongPressed) {
//		// change mode
//		for (win = UPPER; win <= BLING; win++) {
//			set_led(TOPSIDE, win+LED13, WHITE);
//			set_led(TOPSIDE, mode_step[currModeStep[win]].nr, displayColor[TOPSIDE][win]);
//			write_ledColumn(TOPSIDE);
//			wait_ledColumn();
//
//			while (! ButtonReleased) {
//				// wait till button released
//				wait_10ms(2);
//			}
//			ButtonPressed = FALSE;
//			ButtonReleased = FALSE;
//			ButtonLongPressed = FALSE;
//
//			while(1) {
//				// choose mode for win
//				wait_10ms(20);
//				if (ButtonLongPressed) {
//					// mode choosen
//					ButtonLongPressed = FALSE;
//					break;
//				} else if (ButtonReleased) {
//					// next mode step
//					ButtonReleased = FALSE;
//					if (++currModeStep[win] == MODE_STEPS) {
//						currModeStep[win] = 0;
//					}
//					clear_leds(TOPSIDE);
//					set_led(TOPSIDE, win+LED13, WHITE);
//					set_led(TOPSIDE, mode_step[currModeStep[win]].nr, displayColor[TOPSIDE][win]);
//					write_ledColumn(TOPSIDE);
//					displayMode[TOPSIDE][win] = mode_step[currModeStep[win]].display_mode;
//					cycloMode[TOPSIDE][win] = mode_step[currModeStep[win]].cyclo_mode;
//				}
//			}
//
//			clear_leds(TOPSIDE);
//			write_ledColumn(TOPSIDE);
//			while (! ButtonReleased) {
//				// wait till button released
//				wait_10ms(2);
//			}
//			ButtonPressed = FALSE;
//			ButtonReleased = FALSE;
//			ButtonLongPressed = FALSE;
//
//			set_led(TOPSIDE, win+LED13, WHITE);
//			set_led(TOPSIDE, mode_step[currModeStep[win]].nr, displayColor[TOPSIDE][win]);
//			write_ledColumn(TOPSIDE);
//
//			while(1) {
//				// choose color for win
//				wait_10ms(2);
//				if (ButtonLongPressed) {
//					// mode choosen
//					ButtonLongPressed = FALSE;
//					break;
//				} else if (ButtonReleased) {
//					// next mode step
//					ButtonReleased = FALSE;
//					if (++displayColor[TOPSIDE][win] == (WHITE+1)) {
//						displayColor[TOPSIDE][win] = RED;
//					}
//					set_led(TOPSIDE, mode_step[currModeStep[win]].nr, displayColor[TOPSIDE][win]);
//					write_ledColumn(TOPSIDE);
//				}
//			}
//			clear_leds(TOPSIDE);
//			write_ledColumn(TOPSIDE);
//		} /* for */
//		while (! ButtonReleased) {
//			// wait till button released
//			wait_10ms(2);
//		}
//		ButtonReleased = FALSE;
//		ButtonPressed = FALSE;
//		ButtonLongPressed = FALSE;


		// toggle low energy mode
		if (low_energy) {
			low_energy = FALSE;
			set_led(TOPSIDE, LED1, WHITE);
		} else {
			low_energy = TRUE;
			set_led(TOPSIDE, LED1, YELLOW);
		}
		write_ledColumn(TOPSIDE);
		wait_10ms(100);
		clear_leds(TOPSIDE);
		write_ledColumn(TOPSIDE);
		wait_ledColumn();

		ButtonReleased = FALSE;
		ButtonPressed = FALSE;
		ButtonLongPressed = FALSE;		
		
	} else {
		// start/stop trip
		ButtonPressed = FALSE;
		ButtonReleased = FALSE;
		
		if (tripMode == TRIP_STOPPED) {
			// stopped -> start trip
			tripMode = TRIP_STARTED;
			chronoMode = TRIP_STARTED;
			set_led(TOPSIDE, LED1, GREEN);
		} else {
			// started (or paused) -> stop trip
			tripMode = TRIP_STOPPED;
			chronoMode = TRIP_STOPPED;
			set_led(TOPSIDE, LED1, RED);	
			// save the configuration and data
			set_params();
			save_params();
		}
		write_ledColumn(TOPSIDE);
		
		wait_10ms(100);
		if (ButtonPressed) {
			// reset trip
			set_led(TOPSIDE, LED1, BLUE);
			write_ledColumn(TOPSIDE);
			tripDistance = 0.0;
			maxSpeed = 0.0;
			avgSpeed = 0.0;
			tripElevationGain = 0.0;
			maxAltitude = 0.0;
			chronoTime = 0.0;
			tripTime = 0.0;
			while (! ButtonReleased) {
				// wait till button released
				wait_10ms(2);
			}
			ButtonPressed = FALSE;
			ButtonReleased = FALSE;
			ButtonLongPressed = FALSE;		
			wait_10ms(100);
		}
		clear_leds(TOPSIDE);
		write_ledColumn(TOPSIDE);
		wait_ledColumn();
	}
	operating_mode = NORMAL;
}


/*
 ** ===================================================================
 **  Method      :  time2str
 */
/**
 *  @brief
 *  	Prints time in seconds as string, format DDdHH:MM:SS [am/pm]
 */
/* ===================================================================*/
static void time2str(double time, char* str) {
	int days, rest, hours, minutes, seconds;
	char s[20];
	
	days = time / (24 * 60 * 60);
	rest = fmod(time, 24 * 60 * 60);
	hours = rest / (60 * 60);
	rest = rest % (60 * 60);
	minutes = rest / 60;
	seconds = rest % 60;

	strcpy(str, " ");
	ltoa(days, s);
	strcat(str, s);
	strcat(str, "d ");
	itoa2(hours, s);
	strcat(str, s);		
	strcat(str, ":");
	itoa2(minutes, s);
	strcat(str, s);
	strcat(str, ":");
	itoa2(seconds, s);
	strcat(str, s);
}

/** ===================================================================
 **  Method      :  realtime2str
 */
/**
 *  @brief
 *  	Prints real time as string, format HH:MM:SS [am/pm]
 */
/* ===================================================================*/
static void realtime2str(char* str) {
	char s[20];
	char ampm[4] = "";

	LDD_RTC_TTime timePtr;

	RTC1_GetTime(NULL, &timePtr);

	strcpy(str, "  ");
	if (imperialUnits) {
		// imperial units
		if (timePtr.Hour > 12) {
			itoa2(timePtr.Hour - 12, s);
			strcpy(ampm, " pm");
		} else {
			itoa2(timePtr.Hour, s);
			strcpy(ampm, " am");			
		}
		strcat(str, s);
	} else {
		// metric units
		itoa2(timePtr.Hour, s);
		strcat(str, s);
	}
	
	strcat(str, ":");
	itoa2(timePtr.Minute, s);
	strcat(str, s);
	strcat(str, ":");
	itoa2(timePtr.Second, s);
	strcat(str, s);

	strcat(str, ampm);	
}

/** ===================================================================
 **  Method      :  realdate2str
 */
/**
 *  @brief
 *  	Prints real time date as string, format dd.mm.yyyy or mm/dd/yyyy 
 */
/* ===================================================================*/
static void realdate2str(char* str) {
	char s[20];

	LDD_RTC_TTime timePtr;

	RTC1_GetTime(NULL, &timePtr);

	strcpy(str, "  "); 
	if (imperialUnits) {
		// imperial units
		itoa2(timePtr.Month, s);
		strcat(str, s);
		strcat(str, "/");
		itoa2(timePtr.Day, s);
		strcat(str, s);
		strcat(str, "/");
		ltoa(timePtr.Year, s);
		strcat(str, s);
	} else {
		// metric units
		itoa2(timePtr.Day, s);
		strcat(str, s);
		strcat(str, ".");
		itoa2(timePtr.Month, s);
		strcat(str, s);
		strcat(str, ".");
		ltoa(timePtr.Year, s);
		strcat(str, s);
	}
}


/*
 ** ===================================================================
 **  Method      :  speed2str
 */
/**
 *  @brief
 *  	Prints speed in km/h or mps as string, format xx.x km/h or xxx.x mph
 */
/* ===================================================================*/
static void speed2str(double speed, char* str) {
	char s[20];
	
	strcpy(str, "  "); 
	if (imperialUnits) {
		// imperial units
		ftoa(currSpeed * 2.236936, 1, s);
		strcat(str, s);
		strcat(str, " mph");	
	} else {
		// metric units
		ftoa(currSpeed * 3.6, 1, s);
		strcat(str, s);
		strcat(str, " km/h");			
	}
}

/*
 ** ===================================================================
 **  Method      :  distance2str
 */
/**
 *  @brief
 *  	Prints distance in km or miles as string, format xx.xkm or xxxmiyyyft
 */
/* ===================================================================*/
static void distance2str(double distance, char* str) {
	char s[20];
	
	strcpy(str, "  "); 
	if (imperialUnits) {
		// imperial units
		double foot = distance * 3.2808399;
		if (foot >= 5280.0) {
			ftoa(foot / 5280, 1, s);
			strcat(str, s);
			strcat(str, " mi ");
		} else {
			ltoa(foot, s);
			strcat(str, s);
			strcat(str, " ft");
		}		
	} else {
		// metric units
		if (distance < 1000.0) {
			ftoa(distance, 0, s);
			strcat(str, s);
			strcat(str, " m");
		} else {
			ftoa(distance / 1000.0, 1, s);
			strcat(str, s);
			strcat(str, " km");
		}			
	}
}

/*
 ** ===================================================================
 **  Method      :  altitude2str
 */
/**
 *  @brief
 *  	Prints altitude in m or ft as string, format xx.xm or xxxft
 */
/* ===================================================================*/
static void altitude2str(double altitude, char* str) {
	char s[20];
	
	strcpy(str, "  "); 
	if (imperialUnits) {
		// imperial units
		ltoa(floor(altitude * 3.2808399 + 0.5), s);
		strcat(str, s); 
		strcat(str, " ft");
	} else {
		// metric units
		ltoa(floor(altitude + 0.5), s);
		strcat(str, s); 
		strcat(str, " m");
	}
}


/*
 ** ===================================================================
 **  Method      :  temperature2str
 */
/**
 *  @brief
 *  	Prints temperature in °C or °F as string
 */
/* ===================================================================*/
static void temperature2str(double temperature, char* str) {
	char s[20];
	
	strcpy(str, "  "); 
	if (imperialUnits) {
		// imperial units
		ftoa(temperature * (9.0 / 5.0) + 32.0, 1, s);
		strcat(str, s);
		strcat(str, " \370F");	
	} else {
		// metric units
		ftoa(temperature, 1, s);
		strcat(str, s);
		strcat(str, " \370C");			
	}
}

/*
** ===================================================================
**  Method      :  mode_Update
*/
/**
 *  @brief
 *  	Changes the displays (upper, lower, and bling on surfaces top & bottom) 
 *  	in accordance to the modes.
 *  	Called every second.
 */
/* ===================================================================*/
void mode_Update() {
	int position;
	char str[40];
	surfaceT sur;
	windowT win;

	if (standby) {
		// not needed in standby mode
		return;
	}
	
	for (sur = TOPSIDE; sur <= BOTTOMSIDE; sur++) {
		for (win = UPPER; win <= LOWER; win++) {
			clear_display(sur, win);
			position = 0;
			switch (displayMode[sur][win]) {
			case CYCLOCOMPUTER:
				switch (cycloMode[sur][win]) {
				case MAXIMUMSPEED:
					speed2str(maxSpeed, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case AVERAGESPEED: 
					speed2str(avgSpeed, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case CURRENTALTITUDE:
					altitude2str(currAltitude, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case TRIPELEVATIONGAIN:
					altitude2str(tripElevationGain, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case TOTALELEVATIONGAIN:
					altitude2str(totalElevationGain, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case MAXALTITUDE:
					altitude2str(maxAltitude, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case INCLINE:
					break;
				case TEMPERATURE:
					temperature2str(temperature, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case TRIPDISTANCE:
					distance2str(tripDistance, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case TOTALDISTANCE:
					distance2str(totalDistance, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case TRIPTIME:
					time2str(tripTime, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case CURRENTTIME:
					realtime2str(str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case CURRENTDATE:
					realdate2str(str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case TOTALTIME:
					time2str(totalTime, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case CHRONOTIME:
					time2str(chronoTime, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				case CURRENTSPEED:
					// fall through
				default:
					speed2str(currSpeed, str);
					position = put_str(str, DOS7x12b, displayColor[sur][win], 0, sur, win);
					break;
				} // switch
				break;
			case STRING:
				put_str(displayString[sur][win], DOS7x12b, displayColor[sur][win], 0, sur, win);
				break;
			case IMAGE:
				put_Image(displayImage[sur][win], 0, sur, win);
				break;
			case LIGHT:
				// puts_12x16("\333\333\333\333\333\333\333\333", front ? WHITE : RED, 0, sur, win);
				break;
			case BLANK:
				put_str(".", DOS5x12, displayColor[sur][win], 0, sur, win);
				break;
			} // switch
		} // for

		switch (displayMode[sur][BLING]) {
		case IMAGE:	
			blingOn[sur] = TRUE;
			put_Image(displayImage[sur][BLING], 0, sur, BLING);
			break;
		case STRING:
			blingOn[sur] = TRUE;
			put_str(displayString[sur][BLING], DOS7x12b, displayColor[sur][BLING], 0, sur, BLING);
			break;
		case BLANK:
			// fall through
		default:
			// all others are also blank
			blingOn[sur] = FALSE;
			break;
		}
	}
}
