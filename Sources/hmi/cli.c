/**
 *  @brief
 *      Command Line Interface (CLI, interactive mode)
 *
 *      show [all]
 *      show     currentspeed|speed   float            [m/s]
 *      show     maximumspeed|max     float            [m/s]
 *      show     averagespeed|avg     float            [m/s]
 *      show     tripdistance|trip    float            [m]
 *      show|set totaldistance|tot    float            [m]
 *      show     currentaltitude|alt  float            [m]
 *      show     tripelevationgain|gain float            [m]
 *      show|set totalelevationgain|totgain float            [m]
 *      show     incline|inc          float            [%]
 *      show     temperature|temp     float            [°C]
 *      show     pedalingcadence|cad  float            [/Min]
 *      show	 hallsensor|hall      yes|no
 *      show     oled                 yes|no
 *      set|show energy               low|standard|on
 *
 *      show|set currenttime|watch    yyyymmddhhmmss
 *      show     triptime|time        float            [s]
 *      show|set totaltime|tottime    float            [s]
 *      show     chronotime|chrono    float            [s]
 *
 *      show     datalog
 *
 *      show|set circumference|circ   float            [m]
 *      show|set unit                 imperial|metric
 *      show|set stretch              float
 *      show|set side                 left|right
 *      show|set wheel                front|rear
 *      show|set logintervall|log     float            [s]
 *      show|set delay                float            [°]
 *      show|set surface              top|bottom
 *
 *		show|set upper|lower          speed|max|avg|trip|tot|alt|inc|temp|cad|watch|time|stop|str|blk|img|light
 *		show|set bling                str|blk|img
 *
 *		show|set color upper|lower    rd|gn|yl|bl|ma|cy|wt
 *
 *		show|set pattern              number           [0..49]
 *		rrrrrrrrrrrr
 *		rrrrrwwrrrrr
 *		rrrrrwwrrrrr
 *		rrwwwwwwwwrr
 *		rrwwwwwwwwrr
 *		rrrrrwwrrrrr
 *		rrrrrwwrrrrr
 *		rrrrrrrrrrrr
 *		.
 *
 *		set script               number
 *		command
 *		command
 *		..
 *		;
 *
 *		show|set string upper|lower   anystring
 *		show|set image upper|lower|bling number
 *
 *      ble reset
 *      ble command
 *      ble transparent
 *
 *      log start                      [yyyymmddhhmmss]
 *      log stop
 *
 *      clear logdata
 *
 *      trip start|stop|pause|resume
 *
 *      test
 *      about
 *      help
 *      reset
 *      factory
 *      exit
 *
 *  @file
 *      cli.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2013-12-04
 *  @remark
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 *  @version
 *      Version 4.8, 2017/09/09
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
 *  Message displayed at startup and for the command about
 */
const char helloMessage[] =
		"\n"
		"Euler Wheel 32, Velo Bling Bling\n"
		"--------------------------------\n\n"
		"Version 4.8, 2017/09/09, Copyright Peter Schmid\n\n";


// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "IO_Map.h"

// PE include files
// ****************
#include "Cpu.h"
#include "RTC1.h"
#include "BL600.h"

// application include files
// *************************
#include "definitions.h"
#include "cli.h"
#include "script.h"
#include "visual/led.h"
#include "visual/display.h"
#include "visual/oled.h"
#include "powermgr.h"
#include "comm/usb.h"
#include "test.h"
#include "mode.h"
#include "motion/wheelsensor.h"
#include "cyclo/cyclocomputer.h"
#include "cyclo/datalogger.h"
#include "cyclo/watch.h"
#include "driver/parameter.h"
#include "motion/bling.h"
#include "driver/pmeter.h"
#include "comm/ble.h"
#include "driver/charger.h"
#include "driver/ameter.h"


// strings
// *******

static const char cli_prompt_s[] = "CLI> ";
static const char pattern_prompt_s[] = "PAT> ";
static const char script_prompt_s[] = "SCR> ";


// help strings
// ************

static const char cliHelp[] =
       //01234567890123456789012345678901234567890123456789012345678901234567890123456789
        "Command Line Interface (interactive mode).\n";

static const char cliHelpFull[] =
        "exit\n"
        "show\n"
		"set\n"
        "save\n"
		"trip\n"
		"ble\n"
		"script\n"
        "uptime\n"
        "test\n"
        "fault\n"
        "reset\n"
		"factory\n"
		"about\n"
        "help [<command>]\n";

static const char cliHelpExit[] =
        "exit\n"
        "\n"
        "Exits the interactive mode and goes back to the normal operating mode.\n";

static const char cliHelpTest[] =
        "test\n"
        "\n"
        "Goes to the automatic test mode.\n"
        "This command is only useful for commissioning.\n";

static const char cliHelpShow[] =
        "show currentspeed|maximumspeed|averagespeed|tripdistance|totaldistance\n"
		"show currentaltitude|tripelevation|totalelevation|incline\n"
		"show altimeteroffset\n"
		"show temperature|pedalingcadence\n"
		"show watch|triptime|totaltime|chronotime\n"
		"show datalog\n"
		"show circumference|unit|stretch|side|wheel|logintervall\n"
		"show frontdelay|reardelay|frontbetween|rearbetween\n"
		"show stagecoach\n"
		"show top|lower|bling\n"
		"show image|string\n"
		"show script\n"
		"show pattern\n"
		"show acceleration\n"
		"show battery|energy\n"
		"show hallsensor\n"
		"show oled\n"
		"show script\n"
        "\n"
        "Shows the parameters\n";

static const char cliHelpSet[] =
       //01234567890123456789012345678901234567890123456789012345678901234567890123456789
        "set totaldistance <distance [m]>\n"
        "set totalelevationgain <height [m]>\n"
        "set watch <time [yyyymmddhhmmss]>\n"
        "set totaltime <time [s]>\n"
		"set circumference <length [m]>\n"
		"set altimeteroffset <altitude [m]>\n"
		"set unit metric|imperial\n"
		"set stretch <0.8 .. 1.5>\n"
		"set side left|right\n"
		"set wheel front|rear\n"
		"set frontdelay|reardelay|frontbetween|rearbetween <0 .. 100[°]>\n"
		"set stagecoach <number [pixel/rev]\n>"
		"set energy low|standard|on\n"
		"set hallsensor yes|no\n"
		"set oled yes|no\n"
		"set surface top|bottom\n"
		"set upper|lower speed|max|avg|trip|tot|alt|inc|temp|cad|watch|time|chro|string|blk|img|light\n"
		"set bling blk|img\n"
		"set string upper|lower|bling <string>\n"
		"set image upper|lower|bling <number>\n"
		"set color upper|lower|bling red|green|yellow|blue|magenta|cyan|white\n"
		"set script <number>\n"
		"commands..\n"
		";\n"
		"set pattern <number>\n"
		"drgbymcwdrgbymcw\n"
		"...\n"
		"drgbymcwdrgbymcw\n"
        ".\n"
        "Sets the parameters\n";

static const char cliHelpTrip[] =
        "trip start|stop|pause|resume\n"
		"\n"
		"Starting and stopping the trip\n";

static const char cliHelpSave[] =
        "save\n"
        "\n"
        "Saves the configuration parameters.\n";

static const char cliHelpBle[] =
        "ble\n"
		"ble reset\n"
		"ble command <command> <parameter>\n"
		"ble transparent\n"
        "\n"
        "BLE commands over UART.\n";

static const char cliHelpScript[] =
        "script\n"
		"script start|test <number>\n"
		"script stop\n"
        "\n"
        "Start, stop, and test scripts.\n";

static const char cliHelpUptime[] =
        "uptime\n"
        "\n"
        "Shows the elapsed time since startup.\n";

static const char cliHelpFault[] =
        "fault\n"
        "\n"
        "For test purposes only. Produces a memory fault.\n";

static const char cliHelpFactory[] =
        "factory\n"
        "\n"
        "Restore factory settings.\n";

static const char cliHelpReset[] =
        "reset\n"
        "\n"
        "Resets (restarts) the eWheel.\n";


// command tokens
// **************

static const char totaldistance_s[]   = "totaldistance";
static const char tot_s[]             = "tot";
static const char currentspeed_s[]    = "currentspeed";
static const char speed_s[]           = "speed";
static const char maximumspeed_s[]    = "maximumspeed";
static const char max_s[]             = "max";
static const char averagespeed_s[]    = "averagespeed";
static const char avg_s[]             = "avg";
static const char tripdistance_s[]    = "tripdistance";
static const char trip_s[]            = "trip";
static const char currentaltitude_s[] = "currentaltitude";
static const char alt_s[]             = "alt";
static const char maximumaltitude_s[] = "maximumaltitude";
static const char tripelevationgain_s[]    = "tripelevationgain";
static const char gain_s[]            = "gain";
static const char totalelevationgain_s[]   = "totalelevationgain";
static const char totgain_s[]         = "totgain";
static const char incline_s[]         = "incline";
static const char inc_s[]             = "inc";
static const char altimeteroffset_s[] = "altimeteroffset";
static const char altoff_s[]          = "altoff";
static const char temperature_s[]     = "temperature";
static const char temp_s[]            = "temp";
static const char pedalingcadence_s[] = "pedalingcadence";
static const char cad_s[]             = "cad";
static const char currenttime_s[]     = "currenttime";
static const char watch_s[]           = "watch";
static const char triptime_s[]        = "triptime";
static const char time_s[]            = "time";
static const char totaltime_s[]       = "totaltime";
static const char tottm_s[]           = "tottm";
static const char chronotime_s[]      = "chronotime";
static const char chrono_s[]          = "chrono";
static const char chro_s[]            = "chro";
static const char stop_s[]            = "stop";
static const char datalog_s[]         = "datalog";
static const char data_s[]            = "data";
static const char circumference_s[]   = "circumference";
static const char circ_s[]            = "circ";
static const char stretch_s[]         = "stretch";
static const char stre_s[]            = "stre";
static const char side_s[]            = "side";
static const char wheel_s[]           = "wheel";
static const char whl_s[]             = "whl";
static const char logintervall_s[]    = "logintervall";
static const char log_s[]             = "log";
static const char upper_s[]           = "upper";
static const char up_s[]              = "up";
static const char lower_s[]           = "lower";
static const char lo_s[]              = "lo";
static const char surface_s[]         = "surface";
static const char sur_s[]             = "sur";
static const char top_s[]             = "top";
static const char bottom_s[]          = "bottom";
static const char bot_s[]             = "bot";
static const char bling_s[]           = "bling";
//static const char bl_s[]              = "bl";
static const char imag_s[]            = "image";
static const char img_s[]             = "img";
static const char pattern_s[]         = "pattern";
static const char pat_s[]             = "pat";
static const char light_s[]           = "light";
static const char li_s[]              = "li";
static const char string_s[]          = "string";
static const char str_s[]             = "str";
static const char color_s[]           = "color";
static const char col_s[]             = "col";
static const char unit_s[]            = "unit";
static const char blank_s[]           = "blank";
static const char blk_s[]             = "blk";
static const char all_s[]             = "all";
static const char ble_s[]             = "ble";
static const char command_s[]         = "command";
static const char transparent_s[]     = "transparent";
static const char trans_s[]           = "trans";
static const char battery_s[]         = "battery";
static const char bat_s[]             = "bat";
static const char energy_s[]          = "energy";
static const char en_s[]              = "en";
static const char low_s[]             = "low";
static const char standard_s[]        = "standard";
static const char std_s[]             = "std";
static const char alwayson_s[]        = "alwayson";
static const char on_s[]              = "on";
static const char acceleration_s[]    = "acceleration";
static const char acc_s[]             = "acc";
static const char script_s[]          = "script";
static const char sc_s[]              = "sc";
static const char hallsensor_s[]      = "hallsensor";
static const char hall_s[]            = "hall";
static const char oled_s[]            = "oled";
static const char frontdelay_s[]      = "frontdelay";
static const char fdel_s[]            = "fdel";
static const char reardelay_s[]       = "reardelay";
static const char rdel_s[]            = "rdel";
static const char frontbetween_s[]    = "frontbetween";
static const char fbet_s[]            = "fbet";
static const char rearbetween_s[]     = "rearbetween";
static const char rbet_s[]            = "rbet";
static const char stagecoach_s[]      = "stagecoach";
static const char stco_s[]            = "stco";

static const char red_s[]             = "red";
static const char rd_s[]              = "rd";
static const char r_s[]               = "r";
static const char green_s[]           = "green";
static const char gn_s[]              = "gn";
static const char g_s[]               = "g";
static const char yellow_s[]          = "yellow";
static const char yl_s[]              = "yl";
static const char y_s[]               = "y";
static const char blue_s[]            = "blue";
static const char bl_s[]              = "bl";
static const char b_s[]               = "b";
static const char magenta_s[]         = "magenta";
static const char ma_s[]              = "ma";
static const char m_s[]               = "m";
static const char cyan_s[]            = "cyan";
static const char cy_s[]              = "cy";
static const char c_s[]               = "c";
static const char white_s[]           = "white";
static const char wt_s[]              = "wt";
static const char w_s[]               = "w";
static const char black_s[]           = "black";
static const char bk_s[]              = "bk";
static const char d_s[]               = "d";

static const char imperial_s[]        = "imperial";
static const char metric_s[]          = "metric";

static const char yes_s[]             = "yes";
static const char no_s[]              = "no";

static const char right_s[]           = "right";
static const char left_s[]            = "left";
static const char front_s[]           = "front";
static const char rear_s[]            = "rear";

static const char m_s_s[]             = "m/s";
static const char s_s[]               = "s";
static const char proc_s[]            = "%";
static const char celsius_s[]            = "°C";
static const char deg_s[]             = "°";
static const char Min_s[]             = "/Min";
static const char V_s[]               = "V";
static const char pixel_s[]           = "pixel";

static const char start_s[]           = "start";
static const char pause_s[]           = "pause";
static const char resume_s[]          = "resume";
static const char mode_s[]            = "mode";

static const char exit_s[]            = "exit";
static const char show_s[]            = "show";
static const char set_s[]             = "set";
static const char test_s[]            = "test";
static const char help_s[]            = "help";
static const char about_s[]           = "about";
static const char save_s[]            = "save";
static const char reset_s[]           = "reset";
static const char fault_s[]           = "fault";
static const char uptime_s[]          = "uptime";
static const char factory_s[]         = "factory";

static const char lf_s[]              = "\n";


static const char notImplementedYet_s_s[] = "not implemented yet\n";
static const char syntaxError_s[]    = "Syntax Error\n";
static const char patternError_s[]   = "Pattern Error\n";


// Global Variables
// ****************
int TimeOut = 6000;
bool wheelDetection = TRUE;
bool bleTransparent = FALSE;


operating_modeT operating_mode = NORMAL;

// Local Variables
// ***************
int pattern_number = -1;
int pattern_column = -1;

// generate hard fault
// *******************

static void (*f)(void);

static void cause_hard_fault(void) {
  f(); /* will cause a hard fault, as the function pointer is NULL */
}


// UID 80 bits (20 nibbles)
// ************************

// SIM_UIDMH // 16 (MS 4 nibbles)
// SIM_UIDML // 32
// SIM_UIDL  // 32 (LS 8 nibbles)


/*  ===================================================================
 *     Method      :  puts_ch
 */
/**
 *  @brief
 *      Write a string s to the serial channel
 */
/* ===================================================================*/
void puts_ch(const char *s, channelT ch) {
	switch (ch) {
	case USB_CHANNEL:
		usb_puts(s);
		break;
	case BLE_CHANNEL:
		ble_puts(s);
		break;
	case SCRIPT_CHANNEL:
		// no output
		break;
	default:
		break;
	}
}


/*  ===================================================================
 *     Method      :  windowStr2Enum
 */
/**
 *  @brief
 *      scan a string for windowT enum
 */
/* ===================================================================*/
static windowT windowStr2Enum(const char *s){
	if (       ! strcmp(s, upper_s) || ! strcmp(s, up_s) ) {
		return UPPER;
	} else if (! strcmp(s, lower_s) || ! strcmp(s, lo_s) ) {
		return LOWER;
	} else if (! strcmp(s, bling_s) || ! strcmp(s, bl_s) ) {
		return BLING;
	}
	return -1;
}


/*
 ** ===================================================================
 **  Method      :  showFloat
 */
/**
 *  @brief
 *      Prints a float number and the unit string to USB
 *  @param
 *  	info
 *  @param
 *  	number
 *  @param
 *  	unit	unit string
 *  @param
 *  	prec	precision (0, 1, or 2 digits)
 *  @param
 *  	ch		output channel
 */
/* ===================================================================*/
static void showFloat(const char info[], double number, const char unit[], int prec, channelT ch) {
	char str[40];
	char number_s[20];

	strcpy(str, info);
	strcat(str, " ");
	ftoa(number, prec, number_s);
	strcat(str, number_s);
	strcat(str, " ");
	strcat(str, unit);
	strcat(str, lf_s);
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showWindow
 */
/**
 *  @brief
 *      Prints the window mode
 */
/* ===================================================================*/
static void showWindow(windowT win, channelT ch) {
	char str[40];

	switch (win) {
	case UPPER:
		strcpy(str, upper_s);
		break;
	case LOWER:
		strcpy(str, lower_s);
		break;
	case BLING:
		strcpy(str, bling_s);
		break;
	default:
		break;
	}
	strcat(str, " ");
	switch (displayMode[surface][win]) {
	case CYCLOCOMPUTER:
		// strcat(str, "cyclocomputer ");
		switch (cycloMode[surface][win]) {
		case CURRENTSPEED:
			strcat(str, currentspeed_s);
			break;
		case MAXIMUMSPEED:
			strcat(str, maximumspeed_s);
			break;
		case AVERAGESPEED:
			strcat(str, averagespeed_s);
			break;
		case TRIPDISTANCE:
			strcat(str, tripdistance_s);
			break;
		case TOTALDISTANCE:
			strcat(str, totaldistance_s);
			break;
		case CURRENTALTITUDE:
			strcat(str, currentaltitude_s);
			break;
		case TRIPELEVATIONGAIN:
			strcat(str, tripelevationgain_s);
			break;
		case TOTALELEVATIONGAIN:
			strcat(str, totalelevationgain_s);
			break;
		case MAXALTITUDE:
			strcat(str, maximumaltitude_s);
			break;
		case INCLINE:
			strcat(str, incline_s);
			break;
		case TEMPERATURE:
			strcat(str, temperature_s);
			break;
		case PEDALINGCADENCE:
			strcat(str, pedalingcadence_s);
			break;
		case CURRENTTIME:
			strcat(str, currenttime_s);
			break;
		case CURRENTDATE:
//			strcat(str, currentdate_s);
			break;
		case TRIPTIME:
			strcat(str, triptime_s);
			break;
		case TOTALTIME:
			strcat(str, totaltime_s);
			break;
		case CHRONOTIME:
			strcat(str, chronotime_s);
			break;
		case NOCYCLO:
			break;
		}
		break;
	case STRING:
		strcat(str, string_s);
		break;
	case IMAGE:
		strcat(str, imag_s);
		break;
	case LIGHT:
		strcat(str, light_s);
		break;
	case BLANK:
		strcat(str, blank_s);
		break;
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showString
 */
/**
 *  @brief
 *      Prints the string
 */
/* ===================================================================*/
static void showString(windowT win, channelT ch) {
	char str[60];

	if (win != -1) {
		strcpy(str, string_s);
		strcat(str, " ");
		switch (win) {
		case UPPER:
			strcat(str, upper_s);
			break;
		case LOWER:
			strcat(str, lower_s);
			break;
		case BLING:
			strcat(str, bling_s);
			break;
		default:
			break;
		}
		strcat(str, " ");
		strcat(str, displayString[surface][win]);
		strcat(str, lf_s);
	} else {
		strcpy(str, syntaxError_s);
	}
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showColor
 */
/**
 *  @brief
 *      Prints the color
 */
/* ===================================================================*/
static void showColor(windowT win, channelT ch) {
	char str[40];

	if (win != -1) {
		strcpy(str, color_s);
		strcat(str, " ");
		switch (win) {
		case UPPER:
			strcat(str, upper_s);
			break;
		case LOWER:
			strcat(str, lower_s);
			break;
		case BLING:
			strcat(str, bling_s);
			break;
		default:
			break;
		}
		strcat(str, " ");
		switch (displayColor[surface][win]) {
		case BLACK:
			strcat(str, black_s);
			break;
		case RED:
			strcat(str, red_s);
			break;
		case GREEN:
			strcat(str, green_s);
			break;
		case YELLOW:
			strcat(str, yellow_s);
			break;
		case BLUE:
			strcat(str, blue_s);
			break;
		case MAGENTA:
			strcat(str, magenta_s);
			break;
		case CYAN:
			strcat(str, cyan_s);
			break;
		case WHITE:
			strcat(str, white_s);
			break;
		}
		strcat(str, lf_s);
	} else {
		strcpy(str, syntaxError_s);
	}
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showImage
 */
/**
 *  @brief
 *      Prints the image number
 */
/* ===================================================================*/
static void showImage(windowT win, channelT ch) {
	char str[40];
	char s[10];

	if (win != -1) {
		strcpy(str, imag_s);
		strcat(str, " ");
		switch (win) {
		case UPPER:
			strcat(str, upper_s);
			break;
		case LOWER:
			strcat(str, lower_s);
			break;
		case BLING:
			strcat(str, bling_s);
			break;
		default:
			break;
		}
		strcat(str, " ");
		ltoa(displayImage[surface][win], s);
		strcat(str, s);
		strcat(str, lf_s);
	} else {
		strcpy(str, syntaxError_s);
	}
	puts_ch(str, ch);
}




/*
 ** ===================================================================
 **  Method      :  showUnit
 */
/**
 *  @brief
 *      Prints the unit metric|imperial
 */
/* ===================================================================*/
static void showUnit(channelT ch) {
	char str[40];

	strcpy(str, unit_s);
	strcat(str, " ");
	if (imperialUnits) {
		strcat(str, imperial_s);
	} else {
		strcat(str, metric_s);
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showSide
 */
/**
 *  @brief
 *      Prints the side left|right
 */
/* ===================================================================*/
static void showSide(channelT ch) {
	char str[40];

	strcpy(str, side_s);
	strcat(str, " ");
	if (right) {
		strcat(str, right_s);
	} else {
		strcat(str, left_s);
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showWheel
 */
/**
 *  @brief
 *      Prints the wheel front|rear
 */
/* ===================================================================*/
static void showWheel(channelT ch) {
	char str[40];

	strcpy(str, wheel_s);
	strcat(str, " ");
	if (front) {
		strcat(str, front_s);
	} else {
		strcat(str, rear_s);
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showTime
 */
/**
 *  @brief
 *      Prints the time yyyymmddhhmmss
 */
/* ===================================================================*/
static void showTime(channelT ch) {
	char str[40];
	char s[10];

	LDD_RTC_TTime timePtr;

	RTC1_GetTime(watchPtr, &timePtr);

	ltoa(timePtr.Year, str);
	itoa2(timePtr.Month, s);
	strcat(str, s);
	itoa2(timePtr.Day, s);
	strcat(str, s);
	itoa2(timePtr.Hour, s);
	strcat(str, s);
	itoa2(timePtr.Minute, s);
	strcat(str, s);
	itoa2(timePtr.Second, s);
	strcat(str, s);
	strcat(str, lf_s);
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showTripMode
 */
/**
 *  @brief
 *      Prints the trip mode
 */
/* ===================================================================*/
static void showTripMode(channelT ch) {
	char str[40];

	strcpy(str, trip_s);
	switch (tripMode) {
	case TRIP_STARTED:
		strcat(str, " started");
		break;
	case TRIP_PAUSED:
		strcat(str, " paused");
		break;
	case TRIP_STOPPED:
		strcat(str, " stopped");
		break;
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showChronoMode
 */
/**
 *  @brief
 *      Prints the chrono mode
 */
/* ===================================================================*/
static void showChronoMode(channelT ch) {
	char str[40];

	strcpy(str, chrono_s);
	switch (chronoMode) {
	case TRIP_STARTED:
		strcat(str, " started");
		break;
	case TRIP_PAUSED:
		strcat(str, " paused");
		break;
	case TRIP_STOPPED:
		strcat(str, " stopped");
		break;
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showSurface
 */
/**
 *  @brief
 *      Prints the surface side
 */
/* ===================================================================*/
static void showSurface(channelT ch) {
	char str[40];

	strcpy(str, surface_s);
	strcat(str, " ");
	switch (surface) {
	case TOPSIDE:
		strcat(str, top_s);
		break;
	case BOTTOMSIDE:
		strcat(str, bottom_s);
		break;
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}


/*
 ** ===================================================================
 **  Method      :  showPattern
 */
/**
 *  @brief
 *      Prints the contents (PATTERN) of an image
 *  @param
 *  	number	image number in ascii
 *  @param
 *  	number
 *  @param
 *  	unit	unit string
 */
/* ===================================================================*/
static void showPattern(const char number_s[], channelT ch) {
	char str[40];
	char num_s[10];
	int number, column, row;
	uint64_t LED;
	LED_colorT color;
	char c;

	number = atoi(number_s);
	itoa2(number, num_s);

	strcpy(str, pattern_s);
	strcat(str, " ");
	strcat(str, num_s);
	strcat(str, "\n");
	puts_ch(str, ch);

	if ((*imageP)[number].length > MAX_COLUMN) {
		puts_ch("Pattern empty\n", ch);
		return;
	}

	for (column=0; column < (*imageP)[number].length; column++) {
		strcpy(str, "");
		LED = (*imageP)[number].dotmatrix[column];
		for (row=0; row<MAX_ROW; row++) {
			color = LED & 07;
			switch (color) {
			case BLACK:
				c = ' ';
				break;
			case RED:
				c = 'r';
				break;
			case GREEN:
				c = 'g';
				break;
			case YELLOW:
				c = 'y';
				break;
			case BLUE:
				c = 'b';
				break;
			case MAGENTA:
				c = 'm';
				break;
			case CYAN:
				c = 'c';
				break;
			case WHITE:
				c = 'w';
				break;
			}
			str[row] = c;
			LED = LED >> 3;
		}
		str[MAX_ROW] = 0;
		strcat(str, "\n");
		puts_ch(str, ch);
	}
	puts_ch(".\n", ch);
}

/*
 ** ===================================================================
 **  Method      :  showAcceleration
 */
/**
 *  @brief
 *      Prints the x/y/z acceleration
 */
/* ===================================================================*/
static void showAcceleration(channelT ch) {
	char str[60];
	char number_s[20];

	strcpy(str, acceleration_s);
	strcat(str, " ");
	ftoa(ameter_X(), 2, number_s);
	strcat(str, number_s);
	strcat(str, " ");
	ftoa(ameter_Y(), 2, number_s);
	strcat(str, number_s);
	strcat(str, " ");
	ftoa(ameter_Z(), 2, number_s);
	strcat(str, number_s);
	strcat(str, " mg, Orientation ");
	ltoa(ameter_getOrientation(), number_s);
	strcat(str, number_s);
	strcat(str, lf_s);
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showEnergy
 */
/**
 *  @brief
 *      Prints the energy mode
 */
/* ===================================================================*/
static void showEnergy(channelT ch) {
	char str[40];

	strcpy(str, energy_s);
	strcat(str, " ");
	switch (energy_mode) {
	case ENERGY_STANDARD:
		strcat(str, standard_s);
		break;
	case ENERGY_LOW:
		strcat(str, low_s);
		break;
	case ENERGY_ALWAYS_ON:
		strcat(str, alwayson_s);
		break;
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showScript
 */
/**
 *  @brief
 *      Prints the script number
 */
/* ===================================================================*/
static void showScript(channelT ch) {
	char str[60];
	char number_s[20];

	strcpy(str, script_s);
	if (scriptExecution) {
		ltoa(currScript, number_s);
		strcat(str, " ");
		strcat(str, number_s);
	} else {
		strcpy(str, script_s);
		strcat(str, " stopped");
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showHallsensor
 */
/**
 *  @brief
 *      Prints the hallsensor
 */
/* ===================================================================*/
static void showHallsensor(channelT ch) {
	char str[40];

	strcpy(str, hallsensor_s);
	strcat(str, " ");
	if (slowHall_Present) {
		strcat(str, yes_s);
	} else {
		strcat(str, no_s);
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showOled
 */
/**
 *  @brief
 *      Prints the oled debug mode.
 */
/* ===================================================================*/
static void showOled(channelT ch) {
	char str[40];

	strcpy(str, oled_s);
	strcat(str, " ");
	if (oled_debug) {
		strcat(str, yes_s);
	} else {
		strcat(str, no_s);
	}
	strcat(str, lf_s);
	puts_ch(str, ch);
}

/*
 ** ===================================================================
 **  Method      :  showAll
 */
/**
 *  @brief
 *      Prints the complete configuration
 */
/* ===================================================================*/
static void showAll(channelT ch) {
	showSurface(ch);

	showWindow(UPPER, ch);
	showWindow(LOWER, ch);
	showWindow(BLING, ch);

	showString(UPPER, ch);
	showString(LOWER, ch);

	showColor(UPPER, ch);
	showColor(LOWER, ch);

	showImage(UPPER, ch);
	showImage(LOWER, ch);
	showImage(BLING, ch);

	showFloat(currentspeed_s, currSpeed, m_s_s, 1, ch);
	showFloat(maximumspeed_s, maxSpeed, m_s_s, 1, ch);
	showFloat(averagespeed_s, avgSpeed, m_s_s, 1, ch);
	showFloat(tripdistance_s, tripDistance, m_s, 1, ch);
	showFloat(totaldistance_s, totalDistance, m_s, 1,ch);
	showFloat(currentaltitude_s, currAltitude, m_s, 0, ch);
	showFloat(tripelevationgain_s, tripElevationGain, m_s, 0, ch);
	showFloat(totalelevationgain_s, totalElevationGain, m_s, 0, ch);
	showFloat(incline_s, incline, proc_s, 0, ch);
	showFloat(altimeteroffset_s, altimeterOffset, m_s, 0, ch);
	showFloat(temperature_s, temperature, celsius_s, 1, ch);
	showFloat(pedalingcadence_s, cadence, Min_s, 0, ch);
	showFloat(triptime_s, tripTime, s_s, 0, ch);
	showFloat(totaltime_s, totalTime, s_s, 0, ch);
	showFloat(chronotime_s, chronoTime, s_s, 0, ch);
	showFloat(circumference_s, circumference, m_s, 2, ch);
	showFloat(stretch_s, stretch, "", 1, ch);
	showFloat(logintervall_s, logIntervall, s_s, 0, ch);
	showFloat(battery_s, batteryVoltage, V_s, 2, ch);
	showEnergy(ch);
	showAcceleration(ch);

	showTripMode(ch);
	showChronoMode(ch);

	showUnit(ch);
	showSide(ch);
	showWheel(ch);
	showTime(ch);

	showHallsensor(ch);
	showOled(ch);

}


/*
 ** ===================================================================
 **  Method      :  setColor
 */
/**
 *  @brief
 *  	dark|red|green|yellow|blue|magenta|cyan|white|
 *      dk|rd|gn|yl|bl|ma|cy|wt
 *      d|r|g|y|b|m|c|w
 *  @param
 *  	str
 *  @param
 *  	color	pointer to color
 */
/* ===================================================================*/
static void setColor(char* str, windowT win, channelT ch) {
	if (win != -1) {
		if (!        strcmp(str, red_s)     || ! strcmp(str, rd_s) || ! strcmp(str, r_s) ) {
			displayColor[surface][win] = RED;
		} else if (! strcmp(str, green_s)   || ! strcmp(str, gn_s) || ! strcmp(str, g_s) ) {
			displayColor[surface][win] = GREEN;
		} else if (! strcmp(str, yellow_s)  || ! strcmp(str, yl_s) || ! strcmp(str, y_s) ) {
			displayColor[surface][win] = YELLOW;
		} else if (! strcmp(str, blue_s)    || ! strcmp(str, bl_s) || ! strcmp(str, b_s) ) {
			displayColor[surface][win] = BLUE;
		} else if (! strcmp(str, magenta_s) || ! strcmp(str, ma_s) || ! strcmp(str, m_s) ) {
			displayColor[surface][win] = MAGENTA;
		} else if (! strcmp(str, cyan_s)    || ! strcmp(str, cy_s) || ! strcmp(str, c_s) ) {
			displayColor[surface][win] = CYAN;
		} else if (! strcmp(str, white_s)   || ! strcmp(str, wt_s) || ! strcmp(str, w_s) ) {
			displayColor[surface][win] = WHITE;
		} else if (! strcmp(str, black_s)   || ! strcmp(str, bk_s) || ! strcmp(str, d_s) ) {
			displayColor[surface][win] = BLACK;
		}
	} else {
		puts_ch(syntaxError_s, ch);
	}
}

/*
 ** ===================================================================
 **  Method      :  setWindowMode
 */
/**
 *  @brief
 *      set the mode for a window
 *  @param
 *  	mode	speed|max|avg|trip|tot|alt|inc|temp|cad|watch|time|stop|string|blk|img|light
 *  @param
 *  	win		UPPER/LOWER
 */
/* ===================================================================*/
static void setWindowMode(char* mode, windowT win, channelT ch) {
    if (       ! strcmp(mode, currentspeed_s)    || ! strcmp(mode, speed_s) ) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   CURRENTSPEED;
    } else if (! strcmp(mode, maximumspeed_s)    || ! strcmp(mode, max_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   MAXIMUMSPEED;
    } else if (! strcmp(mode, averagespeed_s)    || ! strcmp(mode, avg_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   AVERAGESPEED;
    } else if (! strcmp(mode, tripdistance_s)    || ! strcmp(mode, trip_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   TRIPDISTANCE;
    } else if (! strcmp(mode, totaldistance_s)   || ! strcmp(mode, tot_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   TOTALDISTANCE;
    } else if (! strcmp(mode, currentaltitude_s) || ! strcmp(mode, alt_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   CURRENTALTITUDE;
    } else if (! strcmp(mode, incline_s)         || ! strcmp(mode, inc_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   INCLINE;
    } else if (! strcmp(mode, temperature_s)     || ! strcmp(mode, temp_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   TEMPERATURE;
    } else if (! strcmp(mode, pedalingcadence_s) || ! strcmp(mode, cad_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   PEDALINGCADENCE;
    } else if (! strcmp(mode, currenttime_s)     || ! strcmp(mode, watch_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   CURRENTTIME;
    } else if (! strcmp(mode, triptime_s)        || ! strcmp(mode, time_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   TRIPTIME;
    } else if (! strcmp(mode, chrono_s)          || ! strcmp(mode, chro_s)) {
    	displayMode[surface][win] = CYCLOCOMPUTER;
    	cycloMode[surface][win] =   CHRONOTIME;
    } else if (! strcmp(mode, string_s)          || ! strcmp(mode, str_s)) {
    	displayMode[surface][win] = STRING;
    	cycloMode[surface][win] =   NOCYCLO;
    } else if (! strcmp(mode, blank_s)           || ! strcmp(mode, blk_s)) {
    	displayMode[surface][win] = BLANK;
    	if (win == BLING) {
    		blingOn[surface] = FALSE;
    	}
    	cycloMode[surface][win] =   NOCYCLO;
    } else if (! strcmp(mode, imag_s)            || ! strcmp(mode, img_s)) {
    	displayMode[surface][win] = IMAGE;
    	if (win == BLING) {
       		blingOn[surface] = TRUE;
       	}
    	cycloMode[surface][win] =   NOCYCLO;
    } else if (! strcmp(mode, light_s)           || ! strcmp(mode, li_s)) {
    	// light is for all windows, but stored in TOPSIDE UPPER only
    	displayMode[TOPSIDE][UPPER] = LIGHT;
    	cycloMode[TOPSIDE][UPPER] =   NOCYCLO;
    } else {
		puts_ch(syntaxError_s, ch);
    }
}

/*
 ** ===================================================================
 **  Method      :  setString
 */
/**
 *  @brief
 *      set a string
 *  @param
 *  	string
 *  @param
 *  	win	UPPER/LOWER/BLING
 */
/* ===================================================================*/
static void setString(char* string, windowT win, channelT ch) {
	if (win != -1) {
		strcpy(displayString[surface][win], string);
	} else {
		puts_ch(syntaxError_s, ch);
	}
}

/*
 ** ===================================================================
 **  Method      :  setImage
 */
/**
 *  @brief
 *      set image number
 *  @param
 *  	string
 *  @param
 *  	win	UPPER/LOWER/BLING
 */
/* ===================================================================*/
static void setImage(char* string, windowT win, channelT ch) {
	if (win != -1) {
		displayImage[surface][win] = atoi(string);
	} else {
		puts_ch(syntaxError_s, ch);
	}
}


/*
 ** ===================================================================
 **  Method      :  setUnit
 */
/**
 *  @brief
 *      set the unit to imperial or metric
 *  @param
 *  	string
 */
/* ===================================================================*/
static void setUnit(char* string, channelT ch) {
	if (!        strcmp(string, metric_s) ) {
		imperialUnits = FALSE;
	} else if (! strcmp(string, imperial_s) ) {
		imperialUnits = TRUE;
	} else {
		puts_ch(syntaxError_s, ch);
	}
}


/*
 ** ===================================================================
 **  Method      :  setSide
 */
/**
 *  @brief
 *      set the side to left or right
 *  @param
 *  	string
 */
/* ===================================================================*/
static void setSide(char* string, channelT ch) {
	if (!        strcmp(string, left_s) ) {
		right = FALSE;
	} else if (! strcmp(string, right_s) ) {
		right = TRUE;
	} else {
		puts_ch(syntaxError_s, ch);
	}
}


/*
 ** ===================================================================
 **  Method      :  setWheel
 */
/**
 *  @brief
 *      set the wheel to front or rear
 *  @param
 *  	string
 */
/* ===================================================================*/
static void setWheel(char* string, channelT ch) {
	if (!        strcmp(string, front_s) ) {
		front = TRUE;
	} else if (! strcmp(string, rear_s) ) {
		front = FALSE;
	} else {
		puts_ch(syntaxError_s, ch);
	}
}


/*
 ** ===================================================================
 **  Method      :  setWatch
 */
/**
 *  @brief
 *      set the watch (current time and date)
 *  @param
 *  	string	yyyymmddhhmmss
 */
/* ===================================================================*/
static void setWatch(char* string, channelT ch) {
	LDD_RTC_TTime timePtr;
	char str[10];

	if (strlen(string) == 14) {
		memcpy(str, string, 4);
		str[4] = 0;
		timePtr.Year = atoi(str);
		if (timePtr.Year >= 2000 && (timePtr.Year < 3000)) {

			memcpy(str, string + 4, 2);
			str[2] = 0;
			timePtr.Month = atoi(str);

			if (timePtr.Month >= 1 && (timePtr.Month <= 12)) {
				memcpy(str, string + 6, 2);
				str[2] = 0;
				timePtr.Day = atoi(str);

				if (timePtr.Day >= 1 && (timePtr.Day <= 31)) {
					memcpy(str, string + 8, 2);
					str[2] = 0;
					timePtr.Hour = atoi(str);

					if (timePtr.Hour >= 0 && (timePtr.Hour <= 23)) {
						memcpy(str, string + 10, 2);
						str[2] = 0;
						timePtr.Minute = atoi(str);

						if (timePtr.Minute >= 0 && (timePtr.Minute <= 59)) {
							memcpy(str, string + 12, 2);
							str[2] = 0;
							timePtr.Second = atoi(str);

							if (timePtr.Second >= 0 && (timePtr.Second <= 59)) {
								if (RTC1_SetTime(watchPtr, &timePtr) == ERR_OK) {
									return;
								}
								else {
									puts_ch("Error: cannot set watch\n", ch);
								}
							}
						}
					}
				}
			}
		}
	}
	puts_ch("Error: wrong date/time format\n", ch);
}

/*
 ** ===================================================================
 **  Method      :  setSurface
 */
/**
 *  @brief
 *      set the surface side to topside or bottomside to front or rear
 *  @param
 *  	string
 */
/* ===================================================================*/
static void setSurface(char* string, channelT ch) {
	if (!        strcmp(string, top_s)  ) {
		surface = TOPSIDE;
	} else if (! strcmp(string, bottom_s)  || ! strcmp(string, bot_s) ) {
		surface = BOTTOMSIDE;
	} else {
		puts_ch(syntaxError_s, ch);
	}
}

/*
 ** ===================================================================
 **  Method      :  setEnergy
 */
/**
 *  @brief
 *      set the energy mode
 *  @param
 *  	string
 */
/* ===================================================================*/
static void setEnergy(char* string, channelT ch) {
	if (!        strcmp(string, low_s) ) {
		energy_mode = ENERGY_LOW;
	} else if (! strcmp(string, standard_s) || ! strcmp(string, std_s) ) {
		energy_mode = ENERGY_STANDARD;
	} else if (! strcmp(string, alwayson_s) || ! strcmp(string, on_s) ) {
		energy_mode = ENERGY_ALWAYS_ON;
	} else {
		puts_ch(syntaxError_s, ch);
	}
}


/*
 ** ===================================================================
 **  Method      :  setPattern
 */
/**
 *  @brief
 *      Sets the contents (pattern) of an image
 *  @param
 *  	number_s	image number in ascii
 */
/* ===================================================================*/
static void setPattern(const char number_s[], channelT ch) {

	pattern_number = atoi(number_s);
	if (pattern_number < 0 || pattern_number >= MAX_IMAGE) {
		puts_ch(syntaxError_s, ch);
		pattern_number = -1;
	} else {
		pattern_column = 0;
	}
}

/*
 ** ===================================================================
 **  Method      :  setHallsensor
 */
/**
 *  @brief
 *      set the hallsensor
 *  @param
 *  	string
 */
/* ===================================================================*/
static void setHallsensor(char* string, channelT ch) {
	if (!        strcmp(string, yes_s) ) {
		slowHall_Present = TRUE;
	} else if (! strcmp(string, no_s) ) {
		slowHall_Present = FALSE;
	} else {
		puts_ch(syntaxError_s, ch);
	}
}

/*
 ** ===================================================================
 **  Method      :  setOled
 */
/**
 *  @brief
 *      set the oled debug mode.
 *  @param
 *  	string
 */
/* ===================================================================*/
static void setOled(char* string, channelT ch) {
	if (!        strcmp(string, yes_s) ) {
		oled_debug = TRUE;
		oled_Init();
	} else if (! strcmp(string, no_s) ) {
		oled_setState(OLED_OFF);
		oled_debug = FALSE;
	} else {
		puts_ch(syntaxError_s, ch);
	}
}


/*
 ** ===================================================================
 **  Method      :  pattern_parse
 */
/**
 *  @brief
 *      Parses one line (column)
 *  @param
 *  	line	string, 16 chars long
 */
/* ===================================================================*/
static void pattern_parse(const char line[], channelT ch) {
	int row;
	uint64_t LED = 0;
	LED_colorT color;

	if (! strcmp(line, ".")) {
		// no more columns
		image_bufferP->length = pattern_column;
		save_Image(pattern_number);
		pattern_number = -1;
		pattern_column = -1;
	} else {
		// next column
		if (strlen(line) != MAX_ROW) {
			pattern_number = -1;
			pattern_column = -1;
			puts_ch(patternError_s, ch);
			return;
		}
		for (row=0; row<MAX_ROW; row++) {
			switch (line[row]) {
			case ' ':
				color = BLACK;
				break;
			case 'r':
				color = RED;
				break;
			case 'g':
				color = GREEN;
				break;
			case 'y':
				color = YELLOW;
				break;
			case 'b':
				color = BLUE;
				break;
			case 'm':
				color = MAGENTA;
				break;
			case 'c':
				color = CYAN;
				break;
			case 'w':
				color = WHITE;
				break;
			default:
				pattern_number = -1;
				pattern_column = -1;
				puts_ch(patternError_s, ch);
				return;
			}
			LED = LED | ((uint64_t)color << (row * 3));
		}
		image_bufferP->dotmatrix[pattern_column++] = LED;
		if (pattern_column > MAX_COLUMN) {
			pattern_number = -1;
			pattern_column = -1;
			puts_ch(patternError_s, ch);
		}
	}
}



/*
 ** ===================================================================
 **  Method      :  cli_parse
 */
/**
 *  @brief
 *      Command line interface
 *
 *  Command line interface. Reads the line and interprets the
 *  command. With command 'exit' the function returns 1, otherwise 0.
 *  - exit<br>
 *  - test<br>
 *  - show
 *  - set
 *  - uptime<br>
 *  - fault<br>
 *  - reset<br>
 *  - help [<command>]
 *  @param
 *  	line	command line
 *  	ch		output channel (USB or BLE)
 *  @return
 *  	0	OK
 *  	1	Exit command
 *
 */
/* ===================================================================*/
int cli_parse(char* line, channelT ch) {
	char out_str[100];
	static char answer[100];
	char *command;
	char *p[6];
	int i;


	// tokenize
	command = strtok(line, " ");
	i = 0;
	while (i < 7) {
		p[i] = strtok(NULL, " ");
		if (p[i] == NULL) {
			break;
		}
		i++;
	}

	if (! strcmp(command, exit_s)) {
		return 1;
	}
	else if (! strcmp(command, help_s)) {
		if (i == 0) {
			puts_ch(cliHelpFull, ch);
		} else {
			if (! strcmp(p[0], exit_s)) {
				puts_ch(cliHelpExit, ch);
			} else if (! strcmp(p[0], show_s)) {
				puts_ch(cliHelpShow, ch);
			} else if (! strcmp(p[0], set_s)) {
				puts_ch(cliHelpSet, ch);
			} else if (! strcmp(p[0], save_s)) {
				puts_ch(cliHelpSave, ch);
			} else if (! strcmp(p[0], trip_s)) {
				puts_ch(cliHelpTrip, ch);
			} else if (! strcmp(p[0], test_s)) {
				puts_ch(cliHelpTest, ch);
			} else if (! strcmp(p[0], uptime_s)) {
				puts_ch(cliHelpUptime, ch);
			} else if (! strcmp(p[0], fault_s)) {
				puts_ch(cliHelpFault, ch);
			} else if (! strcmp(p[0], reset_s)) {
				puts_ch(cliHelpReset, ch);
			} else if (! strcmp(p[0], factory_s)) {
				puts_ch(cliHelpFactory, ch);
			} else if (! strcmp(p[0], ble_s)) {
				puts_ch(cliHelpBle, ch);
			} else if (! strcmp(p[0], script_s)) {
				puts_ch(cliHelpScript, ch);
			} else if (! strcmp(p[0], help_s)) {
				puts_ch(cliHelpFull, ch);
			} else {
				strcpy(out_str, syntaxError_s);
				puts_ch(out_str, ch);
			}
		}
	}
	else if (! strcmp(command, set_s)) {
		switch (i) {
		case 2:
			// fall through
		case 3:
			if (!        strcmp(p[0], totaldistance_s) || ! strcmp(p[0], tot_s)) {
				totalDistance = atof(p[1]);
			} else if (! strcmp(p[0], totalelevationgain_s) || ! strcmp(p[0], totgain_s) ) {
				totalElevationGain = atof(p[1]);
			} else if (! strcmp(p[0], currenttime_s) || ! strcmp(p[0], watch_s) ) {
				// puts_ch(notImplementedYet_s_s);
				setWatch(p[1], ch);
			} else if (! strcmp(p[0], totaltime_s) || ! strcmp(p[0], tottm_s) ) {
				totalTime = atof(p[1]);
			} else if (! strcmp(p[0], datalog_s) || ! strcmp(p[0], data_s) ) {
				puts_ch(notImplementedYet_s_s, ch);
			} else if (! strcmp(p[0], circumference_s) || ! strcmp(p[0], circ_s) ) {
				circumference = atof(p[1]);
			} else if (! strcmp(p[0], unit_s) ) {
				setUnit(p[1], ch);
			} else if (! strcmp(p[0], energy_s) || ! strcmp(p[0], en_s) ) {
				setEnergy(p[1], ch);
			} else if (! strcmp(p[0], stretch_s) || ! strcmp(p[0], data_s) ) {
				stretch = atof(p[1]);
			} else if (! strcmp(p[0], side_s)  ) {
				setSide(p[1], ch);
			} else if (! strcmp(p[0], wheel_s) || ! strcmp(p[0], whl_s) ) {
				setWheel(p[1], ch);
			} else if (! strcmp(p[0], altimeteroffset_s) || ! strcmp(p[0], altoff_s) ) {
				altimeterOffset = pmeter_getAltitudeWO() - atof(p[1]);
			} else if (! strcmp(p[0], logintervall_s) || ! strcmp(p[0], log_s) ) {
				logIntervall = atof(p[1]);
			} else if (! strcmp(p[0], upper_s ) || ! strcmp(p[0], up_s ) ) {
				setWindowMode(p[1], UPPER, ch);
			} else if (! strcmp(p[0], lower_s) || ! strcmp(p[0], lo_s) ) {
				setWindowMode(p[1], LOWER, ch);
			} else if (! strcmp(p[0], bling_s) || ! strcmp(p[0], bl_s)) {
				setWindowMode(p[1], BLING, ch);
			} else if (! strcmp(p[0], surface_s) || ! strcmp(p[0], sur_s) ) {
				setSurface(p[1], ch);
			} else if (! strcmp(p[0], string_s) || ! strcmp(p[0], str_s) ) {
				setString(p[2], windowStr2Enum(p[1]), ch);
			} else if (! strcmp(p[0], color_s) || ! strcmp(p[0], col_s) ) {
				setColor(p[2], windowStr2Enum(p[1]), ch);
			} else if (! strcmp(p[0], imag_s) || ! strcmp(p[0], img_s) ) {
				setImage(p[2], windowStr2Enum(p[1]), ch);
			} else if (! strcmp(p[0], pattern_s) || ! strcmp(p[0], pat_s) ) {
				setPattern(p[1], ch);
			} else if (! strcmp(p[0], script_s) || ! strcmp(p[0], sc_s) ) {
				script_Set(p[1]);
			} else if (! strcmp(p[0], hallsensor_s) || ! strcmp(p[0], hall_s) ) {
				setHallsensor(p[1], ch);
			} else if (! strcmp(p[0], oled_s) ) {
				setOled(p[1], ch);
			} else if (! strcmp(p[0], frontdelay_s) || ! strcmp(p[0], fdel_s) ) {
				delay_front = atof(p[1]);
			} else if (! strcmp(p[0], reardelay_s) || ! strcmp(p[0], rdel_s) ) {
				delay_rear = atof(p[1]);
			} else if (! strcmp(p[0], frontbetween_s) || ! strcmp(p[0], fbet_s) ) {
				between_front = atof(p[1]);
			} else if (! strcmp(p[0], rearbetween_s) || ! strcmp(p[0], rbet_s) ) {
				between_rear = atof(p[1]);
			} else if (! strcmp(p[0], stagecoach_s) || ! strcmp(p[0], stco_s) ) {
				blingStep = atof(p[1]);
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		case 4:
			// break;
		default:
			// parameter count not OK
			puts_ch(syntaxError_s, ch);
			break;
		}
	} else if (! strcmp(command, show_s)) {
		switch (i) {
		case 1:
			if (!        strcmp(p[0], totaldistance_s) || ! strcmp(p[0], tot_s)) {
				showFloat(totaldistance_s, totalDistance, m_s, 1, ch);
			} else if (! strcmp(p[0], currentspeed_s) || ! strcmp(p[0], speed_s) ) {
				showFloat(currentspeed_s, currSpeed, m_s_s, 1, ch);
			} else if (! strcmp(p[0], maximumspeed_s) || ! strcmp(p[0], max_s) ) {
				showFloat(maximumspeed_s, maxSpeed, m_s_s, 1, ch);
			} else if (! strcmp(p[0], averagespeed_s) || ! strcmp(p[0], avg_s) ) {
				showFloat(averagespeed_s, avgSpeed, m_s_s, 1, ch);
			} else if (! strcmp(p[0], tripdistance_s) || ! strcmp(p[0], trip_s) ) {
				showFloat(tripdistance_s, tripDistance, m_s, 1, ch);
			} else if (! strcmp(p[0], currentaltitude_s) || ! strcmp(p[0], alt_s) ) {
				showFloat(currentaltitude_s, currAltitude, m_s, 0, ch);
			} else if (! strcmp(p[0], tripelevationgain_s) || ! strcmp(p[0], gain_s) ) {
				showFloat(tripelevationgain_s, tripElevationGain, m_s, 0, ch);
			} else if (! strcmp(p[0], totalelevationgain_s) || ! strcmp(p[0], totgain_s) ) {
				showFloat(totalelevationgain_s, totalElevationGain, m_s, 0, ch);
			} else if (! strcmp(p[0], incline_s) || ! strcmp(p[0], inc_s) ) {
				showFloat(incline_s, incline, proc_s, 0, ch);
			} else if (! strcmp(p[0], altimeteroffset_s) || ! strcmp(p[0], altoff_s) ) {
				showFloat(altimeteroffset_s, altimeterOffset, m_s, 0, ch);
			} else if (! strcmp(p[0], temperature_s) || ! strcmp(p[0], temp_s) ) {
				showFloat(temperature_s, temperature, celsius_s, 1, ch);
			} else if (! strcmp(p[0], pedalingcadence_s) || ! strcmp(p[0], cad_s) ) {
				showFloat(pedalingcadence_s, cadence, Min_s, 0, ch);
			} else if (! strcmp(p[0], currenttime_s) || ! strcmp(p[0], watch_s) ) {
				showTime(ch);
			} else if (! strcmp(p[0], triptime_s) || ! strcmp(p[0], time_s) ) {
				showFloat(triptime_s, tripTime,  s_s, 0, ch);
			} else if (! strcmp(p[0], totaltime_s) || ! strcmp(p[0], tottm_s) ) {
				showFloat(totaltime_s, totalTime, s_s, 0, ch);
			} else if (! strcmp(p[0], chronotime_s) || ! strcmp(p[0], chrono_s) ) {
				showFloat(chronotime_s, chronoTime, s_s, 0, ch);
			} else if (! strcmp(p[0], datalog_s) || ! strcmp(p[0], data_s) ) {
				puts_ch(notImplementedYet_s_s, ch);
			} else if (! strcmp(p[0], circumference_s) || ! strcmp(p[0], circ_s) ) {
				showFloat(circumference_s, circumference, m_s, 2, ch);
			} else if (! strcmp(p[0], battery_s) || ! strcmp(p[0], bat_s) ) {
				showFloat(battery_s, batteryVoltage, V_s, 2, ch);
			} else if (! strcmp(p[0], acceleration_s) || ! strcmp(p[0], acc_s) ) {
				showAcceleration(ch);
			} else if (! strcmp(p[0], unit_s) ) {
				showUnit(ch);
			} else if (! strcmp(p[0], energy_s) || ! strcmp(p[0], en_s)) {
				showEnergy(ch);
			} else if (! strcmp(p[0], stretch_s) || ! strcmp(p[0], stre_s) ) {
				showFloat(stretch_s, stretch, "", 1, ch);
			} else if (! strcmp(p[0], side_s) ) {
				showSide(ch);
			} else if (! strcmp(p[0], wheel_s) || ! strcmp(p[0], whl_s) ) {
				showWheel(ch);
			} else if (! strcmp(p[0], surface_s) || ! strcmp(p[0], sur_s) ) {
				showSurface(ch);
			} else if (! strcmp(p[0], logintervall_s) || ! strcmp(p[0], log_s) ) {
				showFloat(logintervall_s, logIntervall, s_s, 0, ch);
			} else if (! strcmp(p[0], upper_s) || ! strcmp(p[0], up_s) ) {
				showWindow(UPPER, ch);
			} else if (! strcmp(p[0], lower_s) || ! strcmp(p[0], lo_s) ) {
				showWindow(LOWER, ch);
			} else if (! strcmp(p[0], bling_s) || ! strcmp(p[0], bl_s)) {
				showWindow(BLING, ch);
			} else if (! strcmp(p[0], all_s) ) {
				showAll(ch);
			} else if (! strcmp(p[0], script_s) || ! strcmp(p[0], sc_s) ) {
				showScript(ch);
			} else if (! strcmp(p[0], hallsensor_s) || ! strcmp(p[0], hall_s) ) {
				showHallsensor(ch);
			} else if (! strcmp(p[0], oled_s) ) {
				showOled(ch);
			} else if (! strcmp(p[0], frontdelay_s) || ! strcmp(p[0], fdel_s) ) {
				showFloat(frontdelay_s, delay_front,  deg_s, 0, ch);
			} else if (! strcmp(p[0], reardelay_s) || ! strcmp(p[0], rdel_s) ) {
				showFloat(reardelay_s, delay_rear,  deg_s, 0, ch);
			} else if (! strcmp(p[0], frontbetween_s) || ! strcmp(p[0], fbet_s) ) {
				showFloat(frontbetween_s, between_front,  deg_s, 0, ch);
			} else if (! strcmp(p[0], rearbetween_s) || ! strcmp(p[0], rbet_s) ) {
				showFloat(rearbetween_s, between_rear,  deg_s, 0, ch);
			} else if (! strcmp(p[0], stagecoach_s) || ! strcmp(p[0], stco_s) ) {
				showFloat(stagecoach_s, blingStep,  pixel_s, 0, ch);
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		case 2:
			if (! strcmp(p[0], string_s) || ! strcmp(p[0], str_s) ) {
				showString(windowStr2Enum(p[1]), ch);
			} else if (! strcmp(p[0], color_s) || ! strcmp(p[0], col_s) ) {
				showColor(windowStr2Enum(p[1]), ch);
			} else if (! strcmp(p[0], imag_s) || ! strcmp(p[0], img_s) ) {
				showImage(windowStr2Enum(p[1]), ch);
			} else if (! strcmp(p[0], pattern_s) || ! strcmp(p[0], pat_s) ) {
				showPattern(p[1], ch);
			} else if (! strcmp(p[0], script_s) || ! strcmp(p[0], sc_s) ) {
				script_Show(p[1], ch);
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		default:
			// parameter count not OK
			puts_ch(syntaxError_s, ch);
			break;
		}
	} else if (! strcmp(command, trip_s)) {
		switch (i) {
		case 1:
			if (!        strcmp(p[0], start_s) ) {
				maxSpeed = 0.0;
				avgSpeed = 0.0;
				tripDistance = 0.0;
				tripElevationGain = 0.0;
				maxAltitude = 0.0;
				tripTime = 0.0;
				tripMode = TRIP_STARTED;
			} else if (! strcmp(p[0], stop_s) ) {
				tripMode = TRIP_STOPPED;
			} else if (! strcmp(p[0], pause_s) ) {
				tripMode = TRIP_PAUSED;
			} else if (! strcmp(p[0], resume_s) ) {
				if (tripMode == TRIP_PAUSED) {
					tripMode = TRIP_STARTED;
				}
			} else if (! strcmp(p[0], mode_s) ) {
				showTripMode(ch);
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		default:
			puts_ch(syntaxError_s, ch);
			break;
		}
	} else if (! strcmp(command, script_s) || ! strcmp(command, sc_s)) {
		switch (i) {
		case 1:
			if (! strcmp(p[0], stop_s) ) {
				script_Stop(ch);
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		case 2:
			if (!        strcmp(p[0], start_s) ) {
				script_Start(p[1]);
			} else if (! strcmp(p[0], test_s) ) {
				script_Test(p[1], ch);
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		default:
			puts_ch(syntaxError_s, ch);
			break;
		}
	} else if (! strcmp(command, chronotime_s) || ! strcmp(command, chrono_s)) {
		switch (i) {
		case 1:
			if (!        strcmp(p[0], start_s) ) {
				chronoTime = 0.0;
				chronoMode = TRIP_STARTED;
			} else if (! strcmp(p[0], stop_s) ) {
				chronoMode = TRIP_STOPPED;
			} else if (! strcmp(p[0], pause_s) ) {
				chronoMode = TRIP_PAUSED;
			} else if (! strcmp(p[0], resume_s) ) {
				if (chronoMode == TRIP_PAUSED) {
					chronoMode = TRIP_STARTED;
				}
			} else if (! strcmp(p[0], mode_s) ) {
				showChronoMode(ch);
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		default:
			puts_ch(syntaxError_s, ch);
			break;
		}
	} else if (! strcmp(command, ble_s)) {
		switch (i) {
		case 1:
			if (! strcmp(p[0], reset_s) ) {
				ble_reset();
			} else if (! strcmp(p[0], transparent_s) || ! strcmp(p[0], trans_s)) {
				if (ch == USB_CHANNEL) {
					bleTransparent = TRUE;
				}
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		case 3:
			if (! strcmp(p[0], command_s) ) {
				strcpy(out_str, p[1]);
				strcat(out_str, " ");
				strcat(out_str, p[2]);
				strcat(out_str, "\r");
				ble_command(out_str, answer, sizeof(answer));
				strcat(answer, "\n");
				if (answer[0] == '\n') {
					// ignore first LF
					puts_ch(answer+1, ch);
				} else {
					puts_ch(answer, ch);
				}
			} else {
				puts_ch(syntaxError_s, ch);
			}
			break;
		default:
			puts_ch(syntaxError_s, ch);
			break;
		}
	} else if (! strcmp(command, test_s)) {
		test();
	} else if (! strcmp(command, uptime_s)) {
		showFloat(uptime_s, upTime, s_s, 0, ch);
	} else if (! strcmp(command, fault_s)) {
		cause_hard_fault();
		puts_ch("Hardfault -> panic \n", ch);
	} else if (! strcmp(command, reset_s)) {
		Cpu_SystemReset();
	} else if (! strcmp(command, factory_s)) {
		clear_params();
		Cpu_SystemReset();
	} else if (! strcmp(command, save_s)) {
		set_params();
		save_params();
	} else if (! strcmp(command, about_s)) {
		puts_ch(helloMessage, ch);
		puts_ch(ble_ModuleName, ch);
		puts_ch(" ", ch);
		puts_ch(ble_ModuleAdr, ch);
		puts_ch("\n", ch);
		puts_ch(ameter_Name, ch);
		puts_ch("\n", ch);
		puts_ch(pmeter_Name, ch);
		puts_ch("\n", ch);
	} else if (! strcmp(command, "")) {
		;
	} else {
		puts_ch(syntaxError_s, ch);
	}
	return 0;
}


/*
 ** ===================================================================
 **  Method      :  cli_usb
 */
/**
 *  @brief
 *      Command line interface over USB
 *
 *  Command line interface. Reads the USB console and interprets the
 *  commands. With command 'exit' the function returns.
 *
 *  USB has priority over BLE.
 *
 *  Called by main-loop (ProcessorExpert)
 *
 */
/* ===================================================================*/
void cli_usb() {
	char line[100];
	word count = 0;
	word charsInBuffer;

	operating_mode = INTERACTIVE_USB;
	clear_leds(TOPSIDE);
	LEDred_SetVal();
	LEDgreen_SetVal();
	LEDblue_SetVal();
	write_ledColumn(TOPSIDE);

	usb_puts(cliHelp);
	while (1) {
		if (pattern_number < 0 && !script_set) {
			usb_puts(cli_prompt_s);
		} else {
			if (script_set) {
				usb_puts(script_prompt_s);
			} else {
				usb_puts(pattern_prompt_s);
			}
		}
		if (usb_readline(line, sizeof(line), TimeOut) == ERR_TIMEOUT) {
			// timeout
			usb_puts("\ntimeout!\n");
			operating_mode = NORMAL;
			// cancel pattern and script mode
			pattern_number = -1;
			script_set = FALSE;
			return;
		}
		usb_puts(lf_s);

		if (pattern_number < 0 && ! script_set) {
			// command line
			if (cli_parse(line, USB_CHANNEL) == 1) {
				// exit
				operating_mode = NORMAL;
				return;
			}
		} else {
			// pattern or script
			if (pattern_number >= 0) {
				pattern_parse(line, USB_CHANNEL);
			} else {
				script_Line(line, USB_CHANNEL);
			}
		}

		if (bleTransparent) {
			// transparent mode (like terminal)
			usb_puts("transparent mode, ^D to terminate\n");
			int C = ' ';
			while(1) {
				// ^D terminates the transparent mode
				C = usb_getc(5);
				if (C == 4) {
					bleTransparent = FALSE;
					break;
				} else if (C != ERR_TIMEOUT) {
					// character received
					// usb_putc(C);  // local echo
					line[0] = C;
					line[1] = 0;
					ble_puts(line);
				}
				charsInBuffer = BL600_GetCharsInRxBuf();
				if (charsInBuffer > 0) {
					// there is something to echo
					BL600_RecvBlock((BL600_TComData*) line, charsInBuffer, &count);
					line[count] = 0;
					//usb_puts(line);
					int i;
					for (i=0; i < strlen(line); i++) {
						usb_putc(line[i]);
					}
				}
			}
			continue;
		}

		Cpu_SetOperationMode(DOM_WAIT, NULL, NULL);
	}
}


/*
 ** ===================================================================
 **  Method      :  cli_ble
 */
/**
 *  @brief
 *      Command line interface over BLE
 *
 *  Command line interface. Reads the BLE vSP and interprets the
 *  commands.
 *
 *  Called every 10 ms by operation (not called as long as USB is active)
 *
 */
/* ===================================================================*/
void cli_ble() {
	static char line[100];
	char buffer[50];
	byte error = ERR_RXEMPTY;
	word count = 0;
	word charsInBuffer;

//	static bool first = TRUE;

//	operating_mode = INTERACTIVE_BLE;
//	if (first) {
//		if (pattern_number < 0 && !script_set) {
//			ble_puts("\n");
//			ble_puts(cli_prompt_s);
//		} else {
//			ble_puts("\n");
//			if (script_set) {
//				ble_puts(script_prompt_s);
//			} else {
//				ble_puts(pattern_prompt_s);
//			}
//		}
//		//ble_puts("\r");				// BL600 Serial app needs a CR
//		line[0] = 0;
//		first = FALSE;
//	}

	charsInBuffer = BL600_GetCharsInRxBuf();
	if (charsInBuffer > 0) {
		if (charsInBuffer > 50) {
			charsInBuffer = 50;
		}
		error = BL600_RecvBlock((BL600_TComData*) buffer, charsInBuffer, &count);
		switch (error) {
		case ERR_OK:
			// block received
			buffer[count] = 0;
			if (strlen(buffer) + strlen(line) >= sizeof(line)) {
				// string to long -> throw away
				line[0] = 0;
			} else {
				// append received chars to line
				strcat(line, buffer);
				if (line[strlen(line)-1] == '\r') {
					// EOL -> parse line
					ble_puts("\n");
					line[strlen(line)-1] = 0;
					if (pattern_number < 0 && ! script_set) {
						cli_parse(line, BLE_CHANNEL);
						// ble_puts("\n");
						ble_puts(cli_prompt_s);
					} else {
						// ble_puts("\n");
						if (script_set) {
							script_Line(line, BLE_CHANNEL);
							ble_puts(script_prompt_s);
						} else {
							pattern_parse(line, BLE_CHANNEL);
							ble_puts(pattern_prompt_s);
						}
					}
					// ble_puts("\n");		// BL600 Serial app needs a CR
					line[0] = 0;
				}
		}
			break;
		default:
			// error
			count = 0;
			line[count] = 0;
			break;
		}
	}
	operating_mode = NORMAL;
}


/**
 ** @}
 */
