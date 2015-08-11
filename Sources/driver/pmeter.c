/**
 *  @brief
 *      Pressure sensor meter over I2C Interface
 *      
 *      The I2C master interface is also used for the accelerometer MMA8451QR1.
 *
 *      The pressure sensor Xtrinsic MPL3115A2 is used for measuring the altitude and temperature.
 *      I2C address for pressure sensor is 0x60 (7 bit address), CSL clock 75 kHz.
 *      The internal Oversampling is used, 128 samples, 512 ms 
 *      The data is polled every second
 *      (The internal sample FIFO is used for data acquisition. Acquisition time step is 2 s, 4 values for watermark)
 *      
 *      
 *  @file
 *      pmeter.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-04-16
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

/**
**  @defgroup pmeter_module Pressuremeter module
**  @{
*/         
/* MODULE pmeter */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

// PE include files
// ****************
#include "I2C0.h"
#include "PE_Types.h"
#include "Cpu.h"

// application include files
// *************************
#include "definitions.h"
#include "pmeter.h"
#include "powermgr.h"
#include "comm/usb.h"
#include "cyclo/cyclocomputer.h"
#include "comm/ble.h"


// Data register addresses
// ***********************

#define REGISTER_SIZE 1

#define STATUS 0x00				// status 

#define OUT_P_MSB 0x01			// real-time pressure sample, bits 12-19 of 20 bit
#define OUT_P_CSB 0x02			// real-time pressure sample, bits 4-11
#define OUT_P_LSB 0x03			// real-time pressure sample, bits 0-3

#define OUT_T_MSB 0x04			// real-time temperature sample, bits 4-11 of 12 bit
#define OUT_T_LSB 0x05			// real-time temperature sample, bits 0-3 of 12 bit

#define DR_STATUS 0x06			// data ready status information

#define OUT_P_DELTA_MSB 0x07	// pressure change data, bits 12-19 of 20 bit
#define OUT_P_DELTA_CSB 0x08	// pressure change data, bits 4-11
#define OUT_P_DELTA_LSB 0x09	// pressure change data, bits 0-3

#define OUT_T_DELTA_MSB 0x0A	// temperature change data, bits 4-11 of 12 bit
#define OUT_T_DELTA_LSB 0x0B	// temperature change data, bits 0-3 of 12 bit

#define WHO_AM_I 0X0C			// fixed device ID number (0xC4)

#define F_STATUS 0x0D			// FIFO status
#define F_DATA 0x0E				// FIFO 8-bit data access
#define F_SETUP 0x0F			// FIFO setup
#define TIME_DLY 0x10			// time since FIFO overflow

#define SYSMODE	0x11			// current system mode
#define INT_SOURCE 0x12			// interrupt status

#define PT_DATA_CFG 0x13		// data event flag configuration

#define BAR_IN_MSB 0x14			// barometric input for altitude calculation, bits 8-15
#define BAR_IN_LSB 0x15			// barometric input for altitude calculation, bits 0-7

#define P_TGT_MSB 0x16			// pressure/altitude target value, bits 8-15
#define P_TGT_LSB 0x17			// pressure/altitude target value, bits 0-7

#define T_TGT 0x18				// temperature target value

#define P_WND_MSB 0x19			// pressure/altitude window value, bits 8-15
#define P_WND_LSB 0x1A			// pressure/altitude window value, bits 0-7

#define T_WND 0x1B				// temperature window value

#define P_MIN_MSB 0x1C			// minimum pressure/altitude, bits 12-19
#define P_MIN_CSB 0x1D			// minimum pressure/altitude, bits 4-11
#define P_MIN_LSB 0x1E			// minimum pressure/altitude, bits 0-3

#define T_MIN_MSB 0x1F			// minimum temperature, bits 8-15
#define T_MIN_LSB 0x20			// minimum temperature, bits 0-7

#define P_MAX_MSB 0x21			// maximum pressure/altitude, bits 12-19
#define P_MAX_CSB 0x22			// maximum pressure/altitude, bits 4-11
#define P_MAX_LSB 0x23			// maximum pressure/altitude, bits 0-3

#define T_MAX_MSB 0x24			// maximum temperature, bits 8-15
#define T_MAX_LSB 0x25			// maximum temperature, bits 0-7

#define CTRL_REG_1 0x26			// modes, oversampling
#define CTRL_REG_2 0x27			// acquisition time step
#define CTRL_REG_3 0x28			// interrupt pin configuration
#define CTRL_REG_4 0x28			// interrupt enables
#define CTRL_REG_5 0x2A			// interrupt output pin assignment

#define OFF_P 0x2B				// pressure data offset
#define OFF_T 0x2C				// temperature data offset
#define OFF_H 0x2D				// altitude data offset


// Mask bits
// *********

// CTRL_REG_1
#define OSR128 0b00111000		// oversampling 128
#define STANDBY_SBYB_MASK 0xFE	// standby mode
#define ACTIVE_MASK 0x01		// active mode
#define ALT_MASK 0x80			// altimeter mode

// PT_DATA_CFG
#define DREM_MASK 0x04			// data ready event
#define PDEFE_MASK 0x02			// pressure data ready event 
#define TDEFE_MASK 0x01			// temperature data ready event

// STATUS
#define PTDR_MASK 0x08			// Pressure/Altitude OR temperature data ready


// Local Variables
// ***************
static float Altitude = 0.0;
static float Temperature = 0.0;

// Global Variables
// ****************
LDD_TDeviceData *I2C_DeviceData = NULL;
TDataState DataState;

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
		TDataState *DataState, uint8_t Address, uint8_t RegCount, uint8_t *Buffer) {
	
	LDD_I2C_TBusState BusState;
	
	DataState->Sent = FALSE;
	if (I2C0_MasterSendBlock(I2CPtr, &Address, sizeof(Address), LDD_I2C_NO_SEND_STOP) != ERR_OK) {
		return -4;
	}
	
	waitTimeout = 2; // start the timeout for 40 ms
	while ((! DataState->Sent) && (waitTimeout)) {
		// wait for interrupt
		Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
	}
	
	if (! DataState->Sent) {
		return -1;
	}
	DataState->Received = FALSE;
	if (I2C0_MasterReceiveBlock(I2CPtr, Buffer, RegCount, LDD_I2C_SEND_STOP) != ERR_OK) {
		return -4;
	}
	
	waitTimeout = 2; // start the timeout for 40 ms
	while ((! DataState->Received) && (waitTimeout)) {
		// wait for interrupt
		Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
	}
	
	do {
		I2C0_CheckBus(I2CPtr, &BusState);
	} while (BusState != LDD_I2C_IDLE);
	if (! DataState->Received) {
		return -2;
	}
	return 0;
}

/*
** ===================================================================
**  Method      :  WriteRegs  
*/
/**
 *  @brief
 *  	Writes the I2C registers.
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
 *  	Buffer		Send buffer
 *  @return
 *  				0 successful, < 0 error
 */
/* ===================================================================*/
int WriteRegs(LDD_TDeviceData *I2CPtr,
		TDataState *DataState, uint8_t Address, uint8_t RegCount, uint8_t *Data) {
	
	LDD_I2C_TBusState BusState;
	const uint8_t MAX_REG_COUNT = 16;
	uint8_t SendBuffer[MAX_REG_COUNT];

	SendBuffer[0] = Address;
	memcpy(&SendBuffer[1], Data, RegCount);
	DataState->Sent = FALSE;
	if (I2C0_MasterSendBlock(I2CPtr, &SendBuffer, RegCount + 1, LDD_I2C_SEND_STOP) != ERR_OK) {
		return -4;
	}
	
	waitTimeout = 2; // start the timeout for 40 ms
	while ((! DataState->Sent) && (waitTimeout)) {
		// wait for interrupt
		Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); // enter wait mode -> exit by any interrupt
	}
	
	do {
		I2C0_CheckBus(I2CPtr, &BusState);
	} while(BusState != LDD_I2C_IDLE); 
	if (! DataState->Sent) {
		return -3;
	}
	return 0;
}



/*
** ===================================================================
**  Method      :  pmeter_Init
*/
/**
 *  @brief
 *  	Initialises the pressure sensor (MPL3115A2) and I2C0
 *  	
 */
/* ===================================================================*/
void pmeter_Init() {
	uint8_t Data;

	I2C_DeviceData = I2C0_Init(&DataState);
	
	// prepare slave for send and receive
	if (I2C0_SlaveSendBlock(I2C_DeviceData, I2C_Slave_TxBuffer+1, 4)) {
		usb_puts("I2C Slave Tx Block: can't init\n");
	}
	if (I2C0_SlaveReceiveBlock(I2C_DeviceData, I2C_Slave_RxBuffer, 5)) {
		usb_puts("I2C Slave Rx Block: can't init\n");
	}

	// test read
	if (ReadRegs(I2C_DeviceData, &DataState, CTRL_REG_1, REGISTER_SIZE, &Data)) {
		usb_puts("Initialise pressure sensor: can't read pressure sensor\n");
		return;
	}
		
	pmeter_setStandby();

	// enable data flags for pressure and temperature
	Data = DREM_MASK | PDEFE_MASK | TDEFE_MASK;
	if (WriteRegs(I2C_DeviceData, &DataState, PT_DATA_CFG, REGISTER_SIZE, &Data)) {
		usb_puts("Initialise pressure sensor: can't write PT_DATA_CFG\n");
		return;
	}

	pmeter_setActive();
}


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
int pmeter_acquireData() {
	uint8_t Buffer[5];
	int AltitudeI;
	int16 TemperatureI;
	
	if (ReadRegs(I2C_DeviceData, &DataState, STATUS, REGISTER_SIZE, Buffer)) {
		// usb_puts("Read pressure sensor: can't read STATUS\n");
		return -1;
	}
	if (Buffer[0] & PTDR_MASK) {
		// Altitude or Temperature data ready
		
		// read Altitude and Temperature data
		if (ReadRegs(I2C_DeviceData, &DataState, OUT_P_MSB, 5 * REGISTER_SIZE, Buffer)) {
			usb_puts("Read pressure sensor: can't read OUT_P_MSB\n");
			return -1;
		}
		
		// calculate Altitude
		AltitudeI = (Buffer[0] << 24) | (Buffer[1] << 16) | (Buffer[2] << 8);
		Altitude = AltitudeI / 65536.0;
		
		// calculate Temperature
		TemperatureI = (Buffer[3] << 8) | Buffer[4];
		Temperature = TemperatureI / 256.0;
		
		return 1;
		
	}
	return 0;
}


/*
** ===================================================================
**  Method      :  pmeter_getAltitude
*/
/**
 *  @brief
 *  	Gets the altitude meter over sea level (with offset correction)
 */
/* ===================================================================*/
float pmeter_getAltitude() {
	return Altitude - altimeterOffset;
}


/*
** ===================================================================
**  Method      :  pmeter_getAltitudeWO
*/
/**
 *  @brief
 *  	Gets the altitude meter over sea level (without offset correction)
 */
/* ===================================================================*/
float pmeter_getAltitudeWO() {
	return Altitude;
}

/*
** ===================================================================
**  Method      :  pmeter_getTemperature
*/
/**
 *  @brief
 *  	Gets the temperature.
 *  	
 *  @return
 *  				temperature in degree centigrade
 */
/* ===================================================================*/
float pmeter_getTemperature() {
	return Temperature;
}


/*
** ===================================================================
**  Method      :  pmeter_setActive
*/
/**
 *  @brief
 *  	Sets the pressure sensor to the active mode
 */
/* ===================================================================*/
void pmeter_setActive() {
	uint8_t Data;
	
	// set altimeter active with OSR = 128
	Data = ACTIVE_MASK | ALT_MASK | OSR128;
	if (WriteRegs(I2C_DeviceData, &DataState, CTRL_REG_1, REGISTER_SIZE, &Data)) {
		// usb_puts("Initialise pressure sensor: can't write CTRL_REG_1\n");
		return;
	}
}

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
void pmeter_setStandby() {
	uint8_t Data;
		
	// set altimeter standby with OSR = 128
	Data = ALT_MASK | OSR128;
	if (WriteRegs(I2C_DeviceData, &DataState, CTRL_REG_1, REGISTER_SIZE, &Data)) {
		// usb_puts("Initialise pressure sensor: can't write CTRL_REG_1\n");
		return;
	}

}


/**
** @}
*/
