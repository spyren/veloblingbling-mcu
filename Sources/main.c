/**
 *  @brief
 *      LED lights for bicycles wheels.
 *      16 multi color LEDs on each side (top- and bottom side).
 *      There are two windows (upper and lower) on each side.
 *      The windows are 100 x 16 pixels.
 *      The space between the windows can be filled with a pattern (blingbling)
 *
 *      cyclocomputer functions
 *        speed
 *        maximum speed
 *        average spee
 *        trip distance
 *        total distance
 *        altitude
 *        trip altitude
 *        total altitude
 *        maximum altitude
 *        incline
 *        temperature
 *        pedaling cadence
 *        time and date
 *        trip time
 *        total time
 *        chrono time
 *
 *		other display functions
 *		  string
 *		  image
 *		  light
 *		  blank
 *
 *		Configurable over USB and Bluetooth Low Energy (BLE)
 *  @file
 *      main.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2013-12-04
 *  @remark
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */
/* ###################################################################
**     Filename    : main.c
**     Project     : veloblingbling
**     Processor   : MK22DX256VLF5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-01-03, 15:56, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "BL600.h"
#include "ASerialLdd1.h"
#include "LEDoe.h"
#include "LEDreset.h"
#include "BLlink.h"
#include "BLreset.h"
#include "ModeButton.h"
#include "VAdisable.h"
#include "ReedContact.h"
#include "ChargeStat.h"
#include "UsbSupply.h"
#include "ReedInt.h"
#include "ButtonInt.h"
#include "I2C0.h"
#include "USBpoll.h"
#include "RotTimer.h"
#include "Wakeup.h"
#include "AccInt.h"
#include "RTC1.h"
#include "usb_cdc.h"
#include "FlashMem.h"
#include "IntFlashLdd1.h"
#include "BLlinkInt.h"
#include "ADC.h"
#include "AdcLdd1.h"
#include "VREF.h"
#include "Tick.h"
#include "HallVCC.h"
#include "TU1.h"
#include "TU2.h"
#include "usb_device.h"
#include "USB_LDD.h"
#include "TU3.h"
#include "LEDspi.h"
#include "PTC.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

// application include files
// *************************
#include "led.h"
#include "powermgr.h"
#include "operation.h"
#include "cli.h"
#include "usb.h"
#include "wheelsensor.h"
#include "parameter.h"
#include "bling.h"
#include "pmeter.h"
#include "ble.h"
#include "watch.h"
#include "display.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  powermgr_Init();
  wheel_Init();
  bling_Init();
  display_Init();
  ButtonInt_Init(NULL);
  led_Init();
  usb_Init();					// init USB CDC
  usb_puts(helloMessage);
  pmeter_Init();
  ameter_Init();
  ble_Init();

  flash_Init();

  watch_Init();
  ReedInt_Init(NULL);


  while(1) {
	  operation();
	  cli_usb();
  }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
