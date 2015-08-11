/**
 *  @brief
 *      Handles all events/interrupts.
 *
 *		LEDspi_OnBlockSent
 *		LEDspi_OnBlockReceived
 *			INT_SPI0					high, 5		5 us clock
 *
 *		BL600_OnError
 *			INT_UART0_ERR				high, 5
 *		BL600_OnRxChar
 *		BL600_OnTxChar
 *		BL600_OnFullRxBuf
 *		BL600_OnFreeTxBuf
  *			INT_UART0_RX_TX				high, 5
 *
 *		I2C0_OnMasterBlockSent
 *		I2C0_OnMasterBlockReceived
 *		I2C0_OnSlaveBlockSent
 *		I2C0_OnSlaveBlockReceived
 *		I2C0_OnSlaveRxRequest
 *		I2C0_OnSlaveTxRequest
 *			INT_I2C0					high, 5			SCL 75 kHz
 *
 *		ButtonInt_OnInterrupt
 *		ReedInt_OnInterrupt
 *			INT_PORTD					high, 5
 *
 *		RTC1_OnSecond
 *			INT_RTC_Seconds				low, 10
 *
 *		Wakeup_OnInterrupt
 *			INT_LPTimer					medium, 8
 *
 *		RotTimer_OnCounterRestart
 *			INT_FTM0					medium, 8
 *
 *		USBpoll_OnInterrupt
 *			INT_PIT0					medium, 8

 *		Tick_OnInterrupt
 *			INT_PIT1					medium, 8
 *
 *		FlashMem_OnWriteEnd
 *			INT_FTFL					medium, 8
 *
 *		BLlinkInt_OnInterrupt
 *			INT_PORTC					high, 5
 *
 *		ADC_OnEnd
 *		ADC_OnCalibrationEnd
 *			INT_ADC0					medium, 8
 *
 *  @file
 *      Events.c
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
**     Filename    : Events.c
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
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "I2C0.h"

// application include files
// *************************
#include "powermgr.h"
#include "visual/led.h"
#include "comm/usb.h"
#include "comm/ble.h"
#include "hmi/button.h"
#include "hmi/cli.h"
#include "hmi/mode.h"
#include "motion/wheelsensor.h"
#include "motion/bling.h"
#include "cyclo/watch.h"
#include "driver/ameter.h"
#include "driver/pmeter.h"
#include "driver/charger.h"
#include "driver/parameter.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

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
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

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
void Tick_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	button_Task();
	wheel_checkReed();
	busywait_timeout();
}

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
void ADC_OnEnd(void)
{
  /* Write your code here ... */
	get_BatMeasure();
}

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
void ADC_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

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
void BLlinkInt_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	ble_link();
}

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
void RTC1_OnSecond(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	watch_Synch();
	mode_Update();
	powermgr_Second();
}

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
void Wakeup_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
    wait_int();
}

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
void RotTimer_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	wheel_TimerOverrun();
}

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
void RotTimer_OnChannel0(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	rotTimerCh0 = RotTimer_GetCounterValue(RotTimerPtr);
	wheel_StartColumn();
}

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
void RotTimer_OnChannel1(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	rotTimerCh1 = RotTimer_GetCounterValue(RotTimerPtr);
	bling_StartColumn();
}

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
void USBpoll_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	usb_Task();
}

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
void I2C0_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	TDataState *DataState = (TDataState*)UserDataPtr;
	DataState->Sent = TRUE;
}

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
void I2C0_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	TDataState *DataState = (TDataState*)UserDataPtr;
	DataState->Received = TRUE;
}

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
void ButtonInt_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	sleep_wakeup = TRUE;
}

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
void ReedInt_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	wheel_Synch();
}

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
void BL600_OnError(void)
{
  /* Write your code here ... */
}

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
void BL600_OnRxChar(void)
{
  /* Write your code here ... */
}

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
void BL600_OnTxChar(void)
{
  /* Write your code here ... */
}

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
void BL600_OnFullRxBuf(void)
{
  /* Write your code here ... */
	ble_onFullRxBuf();
}

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
void BL600_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

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
void LEDspi_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	Led_BlockSent = TRUE;
}

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
void LEDspi_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

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
void AccInt_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
	sleep_wakeup = TRUE;
}

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
void I2C0_OnSlaveBlockSent(LDD_TUserData *UserDataPtr)
{
	LDD_I2C_TSize Count;

	Count = I2C0_SlaveGetSentDataNum(I2C_DeviceData);
	// prepare slave for send
	// I2C0_SlaveSendBlock(I2C_DeviceData, I2C_Slave_TxBuffer+1, 4);
}

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
void I2C0_OnSlaveBlockReceived(LDD_TUserData *UserDataPtr)
{
	ble_I2CblockReceived();
}

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
void I2C0_OnSlaveRxRequest(LDD_TUserData *UserDataPtr)
{
	// it receives a 1 byte block for register address or a
	// 5 byte block 1 byte register address and 4 bytes data
	// I2C0_SlaveReceiveBlock(I2C_DeviceData, I2C_Slave_RxBuffer, 5);
}

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
void I2C0_OnSlaveTxRequest(LDD_TUserData *UserDataPtr)
{
	// Slave sends always a 4 byte block
	// I2C0_SlaveSendBlock(I2C_DeviceData, I2C_Slave_TxBuffer+1, 4);
	// prepare data in the transmit buffer

}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
