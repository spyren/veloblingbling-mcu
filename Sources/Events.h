/* ###################################################################
**     Filename    : Events.h
**     Project     : veloblingbling
**     Processor   : MK22DX256VLF5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-01-03, 15:56, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK22DN512MC5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  Tick_OnInterrupt (module Events)
**
**     Component   :  Tick [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void Tick_OnInterrupt(LDD_TUserData *UserDataPtr);

void ADC_OnEnd(void);
/*
** ===================================================================
**     Event       :  ADC_OnEnd (module Events)
**
**     Component   :  ADC [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void ADC_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  ADC_OnCalibrationEnd (module Events)
**
**     Component   :  ADC [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  BLlinkInt_OnInterrupt (module Events)
**
**     Component   :  BLlinkInt [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void BLlinkInt_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  RTC1_OnSecond (module Events)
**
**     Component   :  RTC1 [RTC_LDD]
*/
/*!
**     @brief
**         Called each second if OnSecond event is enabled (see
**         [SetEventMask] and [GetEventMask] methods) and RTC device is
**         enabled. This event is available only if [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void RTC1_OnSecond(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  Wakeup_OnInterrupt (module Events)
**
**     Component   :  Wakeup [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Wakeup_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  RotTimer_OnCounterRestart (module Events)
**
**     Component   :  RotTimer [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void RotTimer_OnCounterRestart(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  RotTimer_OnChannel0 (module Events)
**
**     Component   :  RotTimer [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void RotTimer_OnChannel0(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  RotTimer_OnChannel1 (module Events)
**
**     Component   :  RotTimer [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel1 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void RotTimer_OnChannel1(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  USBpoll_OnInterrupt (module Events)
**
**     Component   :  USBpoll [TimerInt_LDD]
*/
/*!
**     @brief
**         Called if periodic event occur. Component and OnInterrupt
**         event must be enabled. See [SetEventMask] and [GetEventMask]
**         methods. This event is available only if a [Interrupt
**         service/event] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void USBpoll_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C0_OnMasterBlockSent (module Events)
**
**     Component   :  I2C0 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in master mode finishes the
**         transmission of the data successfully. This event is not
**         available for the SLAVE mode and if MasterSendBlock is
**         disabled. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C0_OnMasterBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C0_OnMasterBlockReceived (module Events)
**
**     Component   :  I2C0 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C is in master mode and finishes
**         the reception of the data successfully. This event is not
**         available for the SLAVE mode and if MasterReceiveBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C0_OnMasterBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  ButtonInt_OnInterrupt (module Events)
**
**     Component   :  ButtonInt [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void ButtonInt_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  ReedInt_OnInterrupt (module Events)
**
**     Component   :  ReedInt [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void ReedInt_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  BL600_OnError (module Events)
**
**     Component   :  BL600 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BL600_OnError(void);

/*
** ===================================================================
**     Event       :  BL600_OnRxChar (module Events)
**
**     Component   :  BL600 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BL600_OnRxChar(void);

/*
** ===================================================================
**     Event       :  BL600_OnTxChar (module Events)
**
**     Component   :  BL600 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BL600_OnTxChar(void);

/*
** ===================================================================
**     Event       :  BL600_OnFullRxBuf (module Events)
**
**     Component   :  BL600 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BL600_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  BL600_OnFreeTxBuf (module Events)
**
**     Component   :  BL600 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void BL600_OnFreeTxBuf(void);

/*
** ===================================================================
**     Event       :  LEDspi_OnBlockSent (module Events)
**
**     Component   :  LEDspi [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void LEDspi_OnBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  LEDspi_OnBlockReceived (module Events)
**
**     Component   :  LEDspi [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer. This method is available only if
**         the ReceiveBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void LEDspi_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  AccInt_OnInterrupt (module Events)
**
**     Component   :  AccInt [ExtInt_LDD]
*/
/*!
**     @brief
**         This event is called when an active signal edge/level has
**         occurred.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void AccInt_OnInterrupt(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C0_OnSlaveBlockSent (module Events)
**
**     Component   :  I2C0 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in slave mode finishes the
**         transmission of the data successfully. This event is not
**         available for the MASTER mode and if SlaveSendBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C0_OnSlaveBlockSent(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C0_OnSlaveBlockReceived (module Events)
**
**     Component   :  I2C0 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in slave mode finishes the
**         reception of the data successfully. This event is not
**         available for the MASTER mode and if SlaveReceiveBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C0_OnSlaveBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C0_OnSlaveRxRequest (module Events)
**
**     Component   :  I2C0 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address is set to 0, i.e., the
**         Master requests writing to the slave (the slave will be
**         receiving). After the return from the event call the first
**         data byte receiving starts. This event is not available for
**         the MASTER mode.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C0_OnSlaveRxRequest(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  I2C0_OnSlaveTxRequest (module Events)
**
**     Component   :  I2C0 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address is set to 1, i.e., the
**         Master requests reading from slave (the slave will be
**         sending). After the return from the event call the first
**         data byte sending will start. This event is not available
**         for the MASTER mode.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C0_OnSlaveTxRequest(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
