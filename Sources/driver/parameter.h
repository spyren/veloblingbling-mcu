/**
 *  @brief
 *  	Save, get, and remove configuration and log parameters to the flash memory
 *  	
 *		The internal FLASH memory is used to save persistently the parameters.
 *		128 KiB are reserved for the parameters.
 *		The standard FLASH memory for the program starts at 0x410 and
 *		end at 0x3FFFF (roughly 256 KiB, size 3FBF0)
 *		Now it ends at 0x23FFF.
 *		The FLASH for the parameters starts at 0x24000 and ends at 0x3FFFF (112 kiB)
 *		(see Processor Expert CPU -> Build Options -> MemoryArea2 -> Size 23BF0 [original 3FBF0])
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

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "definitions.h"
#include "visual/display.h"
#include "cyclo/cyclocomputer.h"

/**
**  @addtogroup parameter_module
**  @{
*/         

#define FLASH_BASE_ADR 0x24000			/**< where FLASH memory starts, see also protection region in Cpu Properties */
#define FLASH_RECORD_VALID 0x55

typedef struct configParameter_s {
	/* configuration */
	double circumference;	
	
	/* mode & display */
	bool imperialUnits;
	double delay_front;		
	double between_front;
	double delay_rear;
	double between_rear;
	bool right;	
	bool front;
	double stretch;	
	
	Display_modeT displayMode[BOTTOMSIDE+1][BLING+1];
	Cyclo_modeT cycloMode[BOTTOMSIDE+1][BLING+1];
	char String[BOTTOMSIDE+1][BLING+1][40];
	LED_colorT Color[BOTTOMSIDE+1][BLING+1];
	int Image [BOTTOMSIDE+1][BLING+1];

	/* cyclocomputer */
	double maxSpeed;
	double tripDistance;
	double totalDistance;
	double tripElevationGain;
	double totalElevationGain;
	double maxAltitude;
	double altimeterOffset;
	
	double tripTime;
	double currTime;
	LDD_RTC_TTime watchTime;
		
	uint8_t valid;			// if the config length change, the config is no longer valid
	
} configParameter_s;

/** log parameter is 12 bytes -> 80'000 k / 12 = 6666 Min > 110 h @ 1 S/Min */
typedef struct logParameter_s {
	float tripDistance;
	float altitude;
	float temperature;
} logParameter_s;


extern configParameter_s *configParameterP;		/**< points to the configParameter in the EEPROM */
bool FlashReady;								/**< as long as the FLASH process is ongoing this variable is false */ 

/*
 ** ===================================================================
 **  Method      :  flash_Init
 */
/**
 *  @brief
 *  	Initialises the Flash memory
 */
/* ===================================================================*/
void flash_Init();

/*
 ** ===================================================================
 **  Method      :  set_config
 */
/**
 *  @brief
 *  	copy the parameter to the configuration 
 */
/* ===================================================================*/
void set_config();

/*
 ** ===================================================================
 **  Method      :  set_params
 */
/**
 *  @brief
 *  	copy the configuration to the parameter
 */
/* ===================================================================*/
void set_params();

/*
 ** ===================================================================
 **  Method      :  save_params
 */
/**
 *  @brief
 *  	Saves the configuration parameters into the FLASH
 */
/* ===================================================================*/
void save_params();

/*
 ** ===================================================================
 **  Method      :  get_params
 */
/**
 *  @brief
 *  	Gets the configuration parameters from the FLASH
 */
/* ===================================================================*/
void get_params();

/*
 ** ===================================================================
 **  Method      :  clear_params
 */
/**
 *  @brief
 *  	Clears the configuration parameters into the FLASH
 */
/* ===================================================================*/
void clear_params();

/*
 ** ===================================================================
 **  Method      :  save_logdata
 */
/**
 *  @brief
 *  	Saves the log data parameters into the FLASH
 *  @param
 *  	param	Log data parameter to save to flash
 *  @param
 *  	record_nr	index for the parameter record
 *  	
 */
/* ===================================================================*/
void save_logdata(const int16 record_nr, logParameter_s *param);

/*
 ** ===================================================================
 **  Method      :  get_logdata
 */
/**
 *  @brief
 *  	Gets the log data parameters from the FLASH
 *  @param
 *  	param	Log data parameter to get from flash
 *  @param
 *  	record_nr	index for the parameter record
 */
/* ===================================================================*/
void get_logdata(const int16 record_nr, logParameter_s *param);

/*
 ** ===================================================================
 **  Method      :  erase_flash
 */
/**
 *  @brief
 *  	erases the internal FLASH
 */
/* ===================================================================*/
void erase_flash();

/*!
** @}
*/

///*
// ** ===================================================================
// **  Method      :  EEPROM_Init
// */
///**
// *  @brief
// *  	Initialises from the EEPROM memory
// *  	
// */
///* ===================================================================*/
//void EEPROM_Init();

///*
// ** ===================================================================
// **  Method      :  set_config
// */
///**
// *  @brief
// *  	Copies the configuration data to the configParameterP in EEPROM.
// *  	(initialise from global variables)
// */
///* ===================================================================*/
//void set_config();

///*
// ** ===================================================================
// **  Method      :  set_parameter
// */
///**
// *  @brief
// *  	Copies the configParameterP (EEPROM) to the configuration 
// *  	data (parameter).
// */
///* ===================================================================*/
//void set_parameter();

///*
// ** ===================================================================
// **  Method      :  clear_config
// */
///**
// *  @brief
//  *  	Clears the configuration parameters into the EEPROM.
// */
///* ===================================================================*/
//void clear_config();


#endif /* PARAMETER_H_ */
