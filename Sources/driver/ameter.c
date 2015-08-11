/**
 *  @brief
 *      Accelerometer over I2C Master Interface
 *
 *      The accelerometer MMA8451QR1 is used for wake up from deep sleep by
 *      automatic motion detection.
 *
 *      I2C address is 0x1C (7 bit address), CSL clock 75 kHz.
 *      Output INT1 is used for wakeup over AccInt (PTA1, Pin 18).
 *
 *      Y axis changes if the wheel rotates.
 *
 *  @file
 *      ameter.c
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
**  @defgroup ameter_module Accelerometer module
**  @{
*/
/* MODULE ameter */

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
#include "AccInt.h"

// application include files
// *************************
#include "definitions.h"
#include "ameter.h"
#include "comm/usb.h"
#include "pmeter.h"


/* Data register addresses */
#define OUT_X_MSB 0x01
#define OUT_X_LSB 0x02
#define OUT_Y_MSB 0x03
#define OUT_Y_LSB 0x04
#define OUT_Z_MSB 0x05
#define OUT_Z_LSB 0x06

/* System control 1 register addresses */
#define CTRL_REG_1 0x2A
/* External 3-axis accelerometer control register bit masks */
#define ACTIVE_BIT_MASK 0x01	// 0: STANDBY mode; 1: ACTIVE mode
#define F_READ_BIT_MASK 0x02	// 0: only 8-bit data, 1: fast read mode
#define LNOISE_BIT_MASK 0x04	// Reduced noise reduced Maximum range mode, 1: Reduced Noise mode

#define ASLP_50Hz  0x00	// Auto-WAKE sample frequency when the device is in SLEEP Mode.
#define ASLP_12Hz5 0x40
#define ASLP_6Hz25 0x80
#define ASLP_1Hz56 0xC0
#define ODR_800Hz  0x00 // Output Data Rate
#define ODR_400Hz  0x08
#define ODR_200Hz  0x10
#define ODR_100Hz  0x18
#define ODR_50Hz   0x20
#define ODR_12Hz5  0x28
#define ODR_6Hz25  0x30
#define ODR_1Hz56  0x38


/* System control 2 register addresses */
#define CTRL_REG_2 0x2B

#define SMOD_NORMAL              0x00  // SLEEP mode power scheme selection.
#define SMOD_LOW_NOISE_LOW_POWER 0x08
#define SMOD_HIGH_RESOLUTION     0x10
#define SMOD_LOW_POWER           0x18
#define MOD_NORMAL               0x00  // ACTIVE mode power scheme selection.
#define MOD_LOW_NOISE_LOW_POWER  0x01
#define MOD_HIGH_RESOLUTION      0x02
#define MOD_LOW_POWER            0x03


#define SELF_TEST_ENABLE         0x80
#define SOFTWARE_RESET           0x40
#define AUTO_SLEEP               0x04



/* System control 3 register addresses */
#define CTRL_REG_3 0x2C

/* System control 4 register addresses */
#define CTRL_REG_4 0x2D
#define INT_EN_FF_MT 0x04
#define NT_EN_LNDPR  0x10

/* System control 5 register addresses */
#define CTRL_REG_5 0x2E
#define INT_CFG_FF_MT 0x04
#define INT_CFG_LNDPRT 0x10

/* System interrupt status register address */
#define INT_SOURCE 0x0C
#define SRC_FF_MT 0x04


/* Portrait and landscape configuration */

// Portrait/Landscape Status Register
#define PL_STATUS 0x10

// Portrait/Landscape Configuration Register
#define PL_CFG 0x11
#define PL_EN 0x40


// Portrait/Landscape Debounce Counter
#define PL_DEBOUNCE 0X12

//  Back/Front and Z Compensation Register
#define PL_BF_ZCOMP 0x13

// Portrait/Landscape Threshold and Hysteresis Register
#define PL_THS_REG 0x14


/* Motion/Freefall configuration register address */
#define FF_MT_CONFIG 0x15
#define XEFE 0x08	// Event flag enable on X event.
#define YEFE 0x10	// Event flag enable on Y event
#define ZEFE 0x20	// Event flag enable on Z event.
#define OAE 0x40	// Motion detect (1) / Freefall detect (0) flag selection. Default value: 0.
#define ELE 0x80	// Event Latch Enable: Event flags are latched into FF_MT_SRC register.

/* Motion/Freefall source detection register address */
#define FF_MT_SRC 0x16
#define XHP 0x01	// X Motion Polarity Flag, 0 positive
#define XHE 0x02	// X Motion Flag, 1: Motion has been detected
#define YHP 0x04	// Y Motion Polarity Flag, 0 positive
#define YHE 0x08	// Y Motion Flag, 1: Motion has been detected
#define ZHP 0x10	// Z Motion Polarity Flag, 0 positive
#define ZHE 0x20	// Z Motion Flag, 1: Motion has been detected
#define EA 0x80		// Event Active Flag, 1: one or more event flag has been asserted.

/* Threshold register address */
#define FF_MT_THS 0x17

// The threshold resolution is 0.063g/LSB (14 = 0.9 g)
#define THRESHOLD_0G5 8
#define THRESHOLD_1G 16
#define THRESHOLD_1G2 19
#define THRESHOLD_1G4 22
#define THRESHOLD_1G5 24
#define THRESHOLD_2G 32
#define THRESHOLD_3G 48

#define DBCNTM 0x80		// Debounce counter mode selection, 0: increments or decrements debounce, 1: increments or clears counter

/* Debounce counter register address */
#define FF_MT_COUNT 0x18
#define DEBOUNCE 5
// sets the number of debounce sample counts for the event trigger.

/* CTRL_REG1 System Control 1 Register */
#define ACC_REG_SIZE 1U
#define READ_COUNT 5U

// Local Variables
// ***************

// Global Variables
// ****************
LDD_TDeviceData* AccIntPtr;

/*
** ===================================================================
**  Method      :  ameter_Init
*/
/**
 *  @brief
 *  	Initialises the accelerometer (MMA8451Q)
 *
 */
/* ===================================================================*/
void ameter_Init() {
#ifdef ACCELEROMETER
	uint8_t Data;

	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, AMETER_ADR);

	AccIntPtr = AccInt_Init(NULL);
	// AccInt_Enable(AccIntPtr);

	// test read
	if (ReadRegs(I2C_DeviceData, &DataState, CTRL_REG_1, ACC_REG_SIZE, &Data)) {
		usb_puts("no accelerometer\n");
	} else {
		// go to standby for configuration
		Data = (ODR_12Hz5); /* only 8-bit data */
		if (WriteRegs(I2C_DeviceData, &DataState, CTRL_REG_1, ACC_REG_SIZE, &Data)) {
			usb_puts("Initialise accelerometer: can't write  CTRL_REG_1\n");
		}

		// enable the orientation detection.
		Data = (PL_EN);
		if (WriteRegs(I2C_DeviceData, &DataState, PL_CFG, ACC_REG_SIZE, &Data)) {
			usb_puts("Initialise accelerometer: can't write FF_MT_CONFIG\n");
		}

		// set debounce counter
		Data = 2;
		if (WriteRegs(I2C_DeviceData, &DataState, PL_DEBOUNCE, ACC_REG_SIZE, &Data)) {
			usb_puts("Initialise accelerometer: can't write FF_MT_THS\n");
		}

		// enable interrupt function
		Data = NT_EN_LNDPR;
		if (WriteRegs(I2C_DeviceData, &DataState, CTRL_REG_4, ACC_REG_SIZE, &Data)) {
			usb_puts("Initialise accelerometer: can't write CTRL_REG_4\n");
		}

		// route the orientation interrupt to INT1
		Data = INT_CFG_LNDPRT;
		if (WriteRegs(I2C_DeviceData, &DataState, CTRL_REG_5, ACC_REG_SIZE, &Data)) {
			usb_puts("Initialise accelerometer: can't write CTRL_REG_5\n");
		}

		// activate orientation detection, 50 Hz data rate
		Data = (ACTIVE_BIT_MASK | ODR_12Hz5 ); /* Set active mode */
		if (WriteRegs(I2C_DeviceData, &DataState, CTRL_REG_1, ACC_REG_SIZE, &Data)) {
			usb_puts("Initialise accelerometer: can't write  CTRL_REG_1\n");
		}

		Data = 0;
		if (ReadRegs(I2C_DeviceData, &DataState, CTRL_REG_1, ACC_REG_SIZE, &Data)) {
			usb_puts("Initialise accelerometer: can't read accelerometer\n");
		}
		if (Data != (ACTIVE_BIT_MASK | ODR_12Hz5)) {
			usb_puts("Initialise accelerometer: wrong data written\n");
		}
	}

	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, PMETER_ADR);

#endif
}

/*
** ===================================================================
**  Method      :  ameter_getMotion
*/
/**
 *  @brief
 *  	Get the motion und clear the motion detection interrupt
 *
 */
/* ===================================================================*/
int ameter_getMotion() {
#ifdef ACCELEROMETER
	uint8_t Data;

	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, AMETER_ADR);
	ReadRegs(I2C_DeviceData, &DataState, FF_MT_SRC, ACC_REG_SIZE, &Data);
	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, PMETER_ADR);
	return Data;
#else
	return 0.0;
#endif
}

/*
** ===================================================================
**  Method      :  ameter_getOrientation
*/
/**
 *  @brief
 *  	Get the orientation und clear the orientation detection interrupt
 *
 */
/* ===================================================================*/
int ameter_getOrientation() {
#ifdef ACCELEROMETER
	uint8_t Data;

	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, AMETER_ADR);
	ReadRegs(I2C_DeviceData, &DataState, PL_STATUS, ACC_REG_SIZE, &Data);
	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, PMETER_ADR);
	return Data;
#else
	return 0.0;
#endif
}

/*
** ===================================================================
**  Method      :  ameter_X
*/
/**
 *  @brief
 *  	Read the X acceleration
 *  @return
 *  	X acceleration [m/s^2]
 *
 */
/* ===================================================================*/
float ameter_X() {
#ifdef ACCELEROMETER
	int8_t Data;

	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, AMETER_ADR);
	ReadRegs(I2C_DeviceData, &DataState, OUT_X_MSB, ACC_REG_SIZE, &Data);
	return Data * 9.81 / 64;
	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, PMETER_ADR);
#else
	return 0.0;
#endif
}

/*
** ===================================================================
**  Method      :  ameter_Y
*/
/**
 *  @brief
 *  	Read the Y acceleration
 *  @return
 *  	Y acceleration [m/s^2]
 *
 */
/* ===================================================================*/
float ameter_Y() {
#ifdef ACCELEROMETER
	int8_t Data;

	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, AMETER_ADR);
	ReadRegs(I2C_DeviceData, &DataState, OUT_Y_MSB, ACC_REG_SIZE, &Data);
	return Data * 9.81 / 64;
	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, PMETER_ADR);
#else
	return 0.0;
#endif
}

/*
** ===================================================================
**  Method      :  ameter_Z
*/
/**
 *  @brief
 *  	Read the Z acceleration
 *  @return
 *  	Z acceleration [m/s^2]
 *
 */
/* ===================================================================*/
float ameter_Z() {
#ifdef ACCELEROMETER
	int8_t Data;

	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, AMETER_ADR);
	ReadRegs(I2C_DeviceData, &DataState, OUT_Z_MSB, ACC_REG_SIZE, &Data);
	return Data * 9.81 / 64;
	I2C0_SelectSlaveDevice(I2C_DeviceData, LDD_I2C_ADDRTYPE_7BITS, PMETER_ADR);
#else
	return 0.0;
#endif
}


/**
** @}
*/



