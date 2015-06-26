/**
 *  @brief
 *      Accelerometer over I2C Interface
 *      
 *      The accelerometer is used for detecting the wheel position
 *      
 *  @file
 *      pmeter.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef PMETER_H_
#define PMETER_H_

#include "PE_Types.h"

typedef struct {
  volatile bool Sent;
  volatile bool Received;
} TDataState;

extern LDD_TDeviceData *I2C_DeviceData;
extern TDataState DataState;

#define PMETER_ADR 0x60		// 7 bit I2C address

/*
** ===================================================================
**  Method      :  pmeter_Init
*/
/**
 *  @brief
 *  	Initialises the accelerometer (MMA8451Q) and I2C0
 */
/* ===================================================================*/
void pmeter_Init();

/*
** ===================================================================
**  Method      :  ReadRegs
*/
/**
 *  @brief
 *  	Reads the I2C registers.
 *  	For pressure sensor (MPL3115) and accelerometer (MMA8451QR1).
 *  	For accelerometer set device address (SelectSlaveDevice)
 *
 *  @param
 *  	I2CPtr		Device Data
 *  @param
 *  	DataState	Sent/Received flags
 *  @param
 *  	Address		Register address
 *  @param
 *  	RegCount	Register count in bytes
 *  @param
 *  	Buffer		Receive buffer
 *  @return
 *  				0 successful, < 0 error
 */
/* ===================================================================*/
int ReadRegs(LDD_TDeviceData *I2CPtr,
		TDataState *DataState, uint8_t Address, uint8_t RegCount, uint8_t *Buffer);

/*
** ===================================================================
**  Method      :  WriteRegs
*/
/**
 *  @brief
 *      Pressure sensor meter over I2C Interface
 *
 *      The I2C interface is also used for the accelerometer MMA8451QR1.
 *
 *      The pressure sensor Xtrinsic MPL3115A2 is used for measuring the altitude and temperature.
 *      I2C address is 0x60 (7 bit address), CSL clock 75 kHz.
 *      The internal Oversampling is used, 128 samples, 512 ms
 *      The data is polled every second
 *      (The internal sample FIFO is used for data acquisition. Acquisition time step is 2 s, 4 values for watermark)
 *
 *  @param
 *  	I2CPtr		Device Data
 *  @param
 *  	DataState	Sent/Received flags
 *  @param
 *  	Address		Register address
 *  @param
 *  	RegCount	Register count in bytes
 *  @param
 *  	Buffer		Send buffer
 *  @return
 *  				0 successful, < 0 error
 */
/* ===================================================================*/
int WriteRegs(LDD_TDeviceData *I2CPtr,
		TDataState *DataState, uint8_t Address, uint8_t RegCount, uint8_t *Data);

/*
** ===================================================================
**  Method      :  pmeter_acquireData
*/
/**
 *  @brief
 *  	Reads the data (altitude and temperature) from the MPL3115A2
 *  	
 *  @return
 *  	1	valid data
 *  	0	no new data
 *  	-1	error	
 */
/* ===================================================================*/
int pmeter_acquireData();

/*
** ===================================================================
**  Method      :  pmeter_getAltitude
*/
/**
 *  @brief
 *  	Gets the altitude
 */
/* ===================================================================*/
float pmeter_getAltitude();

/*
** ===================================================================
**  Method      :  pmeter_getAltitudeWO
*/
/**
 *  @brief
 *  	Gets the altitude meter over sea level (without offset correction)
 */
/* ===================================================================*/
float pmeter_getAltitudeWO();

/*
** ===================================================================
**  Method      :  pmeter_getTemperature
*/
/**
 *  @brief
 *  	Gets the temperature.
 *  	
 *  @return
 *  				temperature
 */
/* ===================================================================*/
float pmeter_getTemperature();

/*
** ===================================================================
**  Method      :  pmeter_setActive
*/
/**
 *  @brief
 *  	Sets the pressure sensor to the active mode
 */
/* ===================================================================*/
void pmeter_setActive();

/*
** ===================================================================
**  Method      :  pmeter_setStandby
*/
/**
 *  @brief
 *  	Sets the pressure sensor to the standby mode 
 *  	(power down, no measurements)
 */
/* ===================================================================*/
void pmeter_setStandby();


#endif /* PMETER_H_ */
