/**
 *  @brief
 *  	Save, get, and remove configuration to EEPROM.
 *  	Log parameters and patterns (images) to the flash memory
 *  	
 *  The internal FLASH memory is used to save persistently the parameters.
 *  128 KiB are reserved for the parameters. 
 *  The standard FLASH memory for the program starts at 0x410 and 
 *  end at 0x3FFFF (roughly 256 KiB, size 3FBF0)
 *  Now it ends at 0x23FFF.
 *  The FLASH for the parameters starts at 0x24000 and ends at 0x3FFFF (112 kiB)
 *  (see Processor Expert CPU -> Build Options -> MemoryArea2 -> Size 23BF0 [original 3FBF0])
 *  An erasable block has the size of 2 kiB (0x800).
 *      
 *  @file
 *      parameter.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
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
#include "wheelsensor.h"
#include "cyclocomputer.h"
#include "watch.h"
#include "usb.h"
#include "display.h"
#include "mode.h"
#include "button.h"
#include "led.h"


#define EEPROM_BASE	0x14000000


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
 *  	Initialises from the Flash memory
 *  	
 */
/* ===================================================================*/
void flash_Init() {
	FlashDevicePtr = IntFlashLdd1_Init(NULL);		// init FLASH
	//malloc_ptr = malloc(4);
	if (ButtonPressed) {
		set_led(TOPSIDE, 0, YELLOW);
		write_ledColumn(TOPSIDE);
		wait_ledColumn();

		set_params();
		save_params();
		// initialise some images
		images_Init();

		while (!ButtonReleased) {
			;
		}

		set_led(TOPSIDE, 0, BLACK);
		write_ledColumn(TOPSIDE);
		wait_ledColumn();

	} else {
		get_params();
		if (configParameter.valid == FLASH_RECORD_VALID) {
			set_config();
		} else {
			// no valid data in Flash -> initialise from global variables
			set_params();
			save_params();
			// initialise some images
			images_Init();
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


	/* cyclocomputer */
	maxSpeed 			= configParameter.maxSpeed ;
	tripDistance 		= configParameter.tripDistance;
	totalDistance 		= configParameter.totalDistance;
	tripElevationGain	= configParameter.tripElevationGain;
	totalElevationGain 	= configParameter.totalElevationGain;
	maxAltitude 		= configParameter.maxAltitude;
	altimeterOffset 	= configParameter.altimeterOffset;
	
	tripTime 			= configParameter.tripTime;
	currTime 			= configParameter.currTime;

	memcpy(&watchTime, 	&configParameter.watchTime, sizeof(watchTime));
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

	/* cyclocomputer */
	configParameter.maxSpeed 			= maxSpeed;
	configParameter.tripDistance 		= tripDistance;
	configParameter.totalDistance 		= totalDistance;
	configParameter.tripElevationGain 	= tripElevationGain;
	configParameter.totalElevationGain	= totalElevationGain;
	configParameter.maxAltitude 		= maxAltitude;
	configParameter.altimeterOffset		= altimeterOffset;
	
	configParameter.tripTime 			= tripTime;
	configParameter.currTime 			= currTime;
	
	memcpy(&configParameter.watchTime, &watchTime, sizeof(watchTime));

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
 *  	Saves the log data parameters into the FLASH
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
 *  	Gets the log data parameters from the FLASH
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
 *  	erases the internal FLASH
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
//void EEPROM_Init() {
//	FlashDevicePtr = IntFlashLdd1_Init(NULL);		// init FLASH
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP = (configParameter_s*) EEPROM_BASE;
//	if (configParameterP->valid == FLASH_RECORD_VALID) {
//		set_parameter();
//	} else {
//		// no valid data in Flash -> initialise from global variables
//		set_config();
//	}
//}


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
//void set_config() {
//	/* Make sure the EEE is ready. If not wait for the command to complete */
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->circumference =  circumference;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->front =          front;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->right =          right;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->delay_front =    delay_front;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->between_front =  between_front;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->delay_rear =     delay_rear;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->between_rear =   between_rear;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->stretch =        stretch;
//	
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));  
//	configParameterP->imperialUnits =  imperialUnits;
//
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->tripDistance =   tripDistance;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->totalDistance =  totalDistance;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->maxSpeed =       maxSpeed;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->tripAltitude =   tripAltitude;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->maxAltitude =    maxAltitude;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->totalAltitude =  totalAltitude;
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->currTime =       currTime;
//
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->tripTime =       tripTime;
//		
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	memcpy(&configParameterP->displayMode, &displayMode,   sizeof(displayMode));
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	memcpy(&configParameterP->cycloMode,   &cycloMode,     sizeof(cycloMode));
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	memcpy(&configParameterP->String,      &displayString, sizeof(displayString));
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	memcpy(&configParameterP->Color,       &displayColor,  sizeof(displayColor));
//
//	/* Make sure the EEE is ready. If not wait for the command to complete */
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->valid =          FLASH_RECORD_VALID;
//	
//	/* Make sure the EEE is ready. If not wait for the command to complete */
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//}


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
//void set_parameter() {
//	/* Make sure the EEE is ready. If not wait for the command to complete */
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//
//	circumference =   configParameterP->circumference;
//	front =           configParameterP->front;
//	right =           configParameterP->right;
//	delay_front =     configParameterP->delay_front;
//	between_front =   configParameterP->between_front;
//	delay_rear =      configParameterP->delay_rear;
//	between_rear =    configParameterP->between_rear;
//	stretch =         configParameterP->stretch;
//
//	imperialUnits =   configParameterP->imperialUnits;
//
//	tripDistance =    configParameterP->tripDistance;
//	totalDistance =   configParameterP->totalDistance;
//	maxSpeed =        configParameterP->maxSpeed;
//	tripAltitude =    configParameterP->tripAltitude;
//	maxAltitude =     configParameterP->maxAltitude;
//	totalAltitude =   configParameterP->totalAltitude;
//	currTime =        configParameterP->currTime;
//
//	tripTime =        configParameterP->tripTime;
//	
//	memcpy(&displayMode,   &configParameterP->displayMode, sizeof(displayMode));
//	memcpy(&cycloMode,     &configParameterP->cycloMode,   sizeof(cycloMode));
//	memcpy(&displayString, &configParameterP->String,      sizeof(displayString));
//	memcpy(&displayColor,  &configParameterP->Color,       sizeof(displayColor));
//}


///*
// ** ===================================================================
// **  Method      :  clear_config
// */
///**
// *  @brief
// *  	Clears the configuration parameters into the EEPROM.
// */
///* ===================================================================*/
//void clear_config() {
//
//	/* Make sure the EEE is ready. If not wait for the command to complete */
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//	configParameterP->valid = 0;
//	/* Make sure the EEE is ready. If not wait for the command to complete */
//	while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//
//}



/*!
 ** @}
 */
