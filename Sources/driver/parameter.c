/**
 *  @brief
 *  	Save and get configuration to the flash memory.
 *  	Save and get patterns (images) and scripts to the flash memory.
 *  	Log parameters to the flash memory (not used yet).
 *  	
*		The standard FLASH memory for the program starts at 0x410 and
 *		end at 0x3FFFF (roughly 256 KiB, size 3FBF0).
 *
 *		The K22 has also Flex NVM EEPROM. If the EEPROM is not or partly used,
 *		the Flex NVM Flash can be used for other puposes, without EEPROM there
 *		are additional 64 KiB flash and can be used for other purposes. T
 *		he Flex NVM EEPROM buffer RAM (4 KiB) can be used for other purposes too.
 *		It is used in display module for image_bufferP buffer and for the log buffer.
 *
 *		The Flex NVM 64 KiB Flash block is used for parameters and images now.
 *
 *		The program takes about 150 KiB now. That means there are about 106 KiB
 *		free for logging. To be on the safe side only 64 KiB are used for logging.
 *		The FLASH for the log starts at 0x30000 and ends at
 *		0x3FFFF (64 kiB). See also in the Kinetis Design Studio:
 *		Processor Expert Components
 *		CPU -> Build Options -> Generate linker file -> MemoryArea2
 *		-> Size 2FBF0 [original 3FBF0])
 *		An erasable block has the size of 2 kiB (0x800).
 *
 *  @file
 *      parameter.c
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
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
 **  @defgroup parameter_module Parameter module
 **  @{
 */         
/* MODULE parameter */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
//#include <extras/extras_stdlib.h>

// PE include files
// ****************
#include "PE_Types.h"
#include "FlashMem.h"

// application include files
// *************************
#include "parameter.h"
#include "powermgr.h"
#include "motion/wheelsensor.h"
#include "cyclo/cyclocomputer.h"
#include "cyclo/watch.h"
#include "comm/usb.h"
#include "visual/led.h"
#include "visual/oled.h"
#include "visual/display.h"
#include "hmi/mode.h"
#include "hmi/button.h"
#include "hmi/cli.h"
#include "hmi/script.h"




// Global Variables
// ****************
configParameter_s *configParameterP;
bool FlashReady = FALSE;								/**< as long as the FLASH process is ongoing this variable is false */ 

// Local Variables
// ***************
//static int *malloc_ptr;
configParameter_s configParameter;

static LDD_TDeviceData* FlashDevicePtr;



/*
 ** ===================================================================
 **  Method      :  flash_Init
 */
/**
 *  @brief
 *  	Initializes from the Flash memory
 *  	
 */
/* ===================================================================*/
void flash_Init() {
	if (ButtonPressed) {
		// button pressed on power on -> Restore factory settings
		set_led(TOPSIDE, 0, MAGENTA);
		LEDred_ClrVal();
		LEDblue_ClrVal();
		write_ledColumn(TOPSIDE);
		wait_ledColumn();

		set_params();
		save_params();
		// initialize some images and scripts
		images_Init();
		script_Init();

		while (!ButtonReleased) {
			;
		}

		set_led(TOPSIDE, 0, BLACK);
		LEDred_SetVal();
		LEDblue_SetVal();
		write_ledColumn(TOPSIDE);
		wait_ledColumn();

	} else {
		get_params();
		if (configParameter.valid == FLASH_RECORD_VALID) {
			set_config();
		} else {
			// no valid data in Flash -> initialize from global variables
			set_params();
			save_params();
			// initialize some images and scripts
			images_Init();
			script_Init();
		}
	}
}

/*
 ** ===================================================================
 **  Method      :  set_config
 */
/**
 *  @brief
 *  	copy the parameter to the configuration 
 */
/* ===================================================================*/
void set_config() {
	/* configuration */
	circumference 	= configParameter.circumference;
	
	/* mode & display */
	imperialUnits 	= configParameter.imperialUnits;
	delay_front 	= configParameter.delay_front;		
	between_front 	= configParameter.between_front;
	delay_rear 		= configParameter.delay_rear;
	between_rear 	= configParameter.between_rear;
	right 			= configParameter.right;	
	front 			= configParameter.front;
	stretch 		= configParameter.stretch;	
	
	memcpy(&displayMode, 	&configParameter.displayMode, 	sizeof(displayMode));
	memcpy(&cycloMode, 		&configParameter.cycloMode, 	sizeof(cycloMode));
	memcpy(&displayString, 	&configParameter.String, 		sizeof(displayString));
	memcpy(&displayColor, 	&configParameter.Color, 		sizeof(displayColor));
	memcpy(&displayImage, 	&configParameter.Image, 		sizeof(displayImage));

	currScript		= configParameter.currScript;
	scriptExecution	= configParameter.scriptExecution;

	/* cyclocomputer */
	maxSpeed 			= configParameter.maxSpeed ;
	tripDistance 		= configParameter.tripDistance;
	totalDistance 		= configParameter.totalDistance;
	tripElevationGain	= configParameter.tripElevationGain;
	totalElevationGain 	= configParameter.totalElevationGain;
	maxAltitude 		= configParameter.maxAltitude;
	altimeterOffset 	= configParameter.altimeterOffset;
	
	tripTime 			= configParameter.tripTime;

	memcpy(&watchTime, 	&configParameter.watchTime, sizeof(watchTime));

	oled_debug			= configParameter.oledDebug;

	/* Hardware */
	slowHall_Present	=configParameter.slowHall_Present;
}


/*
 ** ===================================================================
 **  Method      :  set_params
 */
/**
 *  @brief
 *  	copy the configuration to the parameter
 */
/* ===================================================================*/
void set_params() {
	/* configuration */
	configParameter.circumference= circumference;	
	
	/* mode & display */
	configParameter.imperialUnits 	= imperialUnits;
	configParameter.delay_front 	= delay_front;		
	configParameter.between_front 	= between_front;
	configParameter.delay_rear 		= delay_rear;
	configParameter.between_rear 	= between_rear;
	configParameter.right 			= right;	
	configParameter.front 			= front;
	configParameter.stretch 		= stretch;	
	
	memcpy(&configParameter.displayMode, 	&displayMode, 	sizeof(displayMode));
	memcpy(&configParameter.cycloMode, 		&cycloMode, 	sizeof(cycloMode));
	memcpy(&configParameter.String, 		&displayString, sizeof(displayString));
	memcpy(&configParameter.Color, 			&displayColor, 	sizeof(displayColor));
	memcpy(&configParameter.Image, 			&displayImage, 	sizeof(displayImage));

	configParameter.currScript 		= currScript;
	configParameter.scriptExecution	= scriptExecution;

	/* cyclocomputer */
	configParameter.maxSpeed 			= maxSpeed;
	configParameter.tripDistance 		= tripDistance;
	configParameter.totalDistance 		= totalDistance;
	configParameter.tripElevationGain 	= tripElevationGain;
	configParameter.totalElevationGain	= totalElevationGain;
	configParameter.maxAltitude 		= maxAltitude;
	configParameter.altimeterOffset		= altimeterOffset;
	
	configParameter.tripTime 			= tripTime;
	
	memcpy(&configParameter.watchTime, &watchTime, sizeof(watchTime));

	configParameter.oledDebug			= oled_debug;

	/* Hardware */
	configParameter.slowHall_Present 	= slowHall_Present;

	configParameter.valid 			= FLASH_RECORD_VALID;	// if the config length change, the config is no longer valid
}


/*
 ** ===================================================================
 **  Method      :  save_params
 */
/**
 *  @brief
 *  	Saves the configuration parameters into the FLASH
 */
/* ===================================================================*/
void save_params() {
	char str[100];
	FlashMem_TAddress FlashAdr = FLASH_BASE_ADR;

	if (FlashMem_SetBlockFlash((FlashMem_TDataAddress) &configParameter, FlashAdr, sizeof(configParameter)) != ERR_OK) {
		strcpy(str, "\nError: cannot save configuration parameters into FLASH\n");
		usb_puts(str);		
	}
}


/*
 ** ===================================================================
 **  Method      :  get_params
 */
/**
 *  @brief
 *  	Gets the configuration parameters from the FLASH
 */
/* ===================================================================*/
void get_params() {
	FlashMem_TAddress FlashAdr = FLASH_BASE_ADR;

	// get the parameters direct from the memory
	memcpy(&configParameter, (void*) FlashAdr, sizeof(configParameter));
}


/*
 ** ===================================================================
 **  Method      :  clear_params
 */
/**
 *  @brief
 *  	Clears the configuration parameters into the FLASH
 */
/* ===================================================================*/
void clear_params() {

	configParameter.valid = 0;
	save_params();
}

/*
 ** ===================================================================
 **  Method      :  save_logdata
 */
/**
 *  @brief
 *  	Saves the log data parameters into the FLASH (not used yet)
 *  @param
 *  	param	Log data parameter to save to flash
 *  @param
 *  	record_nr	index for the parameter record
 *  	
 */
/* ===================================================================*/
void save_logdata(const int16 record_nr, logParameter_s *param) {
	char str[100];
	FlashMem_TAddress FlashAdr = FLASH_BASE_ADR + sizeof(configParameterP) + record_nr * sizeof(*param);
	
		FlashReady = FALSE;
		if (FlashMem_SetBlockFlash((FlashMem_TDataAddress) param, FlashAdr, sizeof(*param)) != ERR_OK) {
			strcpy(str, "\nError: cannot save log data into FLASH\n");
			usb_puts(str);
			FlashReady = TRUE;			
		}
	
}


/*
 ** ===================================================================
 **  Method      :  get_logdata
 */
/**
 *  @brief
 *  	Gets the log data parameters from the FLASH (not used yet)
 *  @param
 *  	param	Log data parameter to get from flash
 *  @param
 *  	record_nr	index for the parameter record
 */
/* ===================================================================*/
void get_logdata(const int16 record_nr, logParameter_s *param) {
	FlashMem_TAddress FlashAdr = FLASH_BASE_ADR + sizeof(configParameterP) + record_nr * sizeof(logParameter_s);

		// get the parameters direct from the memory
		memcpy(param, (void *) FlashAdr, sizeof(*param));
}


/*
 ** ===================================================================
 **  Method      :  erase_flash
 */
/**
 *  @brief
 *  	erases the internal FLASH (not used yet)
 */
/* ===================================================================*/
void erase_flash() {
	byte sector;
	int error;
	FlashMem_TAddress flash_adr;
	char str[100], tmp_str[20];

	for (sector = 0; sector < 32; sector++) {
		// 32 1 KiB blocks
//		FlashReady = FALSE;
		flash_adr = FLASH_BASE_ADR + IntFlashLdd1_ERASABLE_UNIT_SIZE * sector;
		error = FlashMem_EraseSector(flash_adr);
		if (error != ERR_OK) {
			strcpy(str, "\nError: cannot erase FLASH sector at address ");
			ltoa((long)flash_adr, tmp_str);
			strcat(str, tmp_str);
			strcat(str, "\n");
			usb_puts(str);
			FlashReady = TRUE;
		}
//		while (! FlashReady) {
//			wait_ms(1);
//		}
	}
}





/*!
 ** @}
 */
