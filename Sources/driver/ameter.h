/**
 *  @brief
 *      Accelerometer over I2C Interface
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

#ifndef AMETER_H_
#define AMETER_H_

#define AMETER_ADR 0x1C		// 7 bit I2C address

extern LDD_TDeviceData* AccIntPtr;
extern char I2C_Slave_Buffer[];
extern char ameter_Name[];
extern bool ameter_Present;



/*
** ===================================================================
**  Method      :  ameter_Init
*/
/**
 *  @brief
 *  	Initialises the accelerometer (MMA8451Q) and I2C0
 *
 *  	+-2 g resolution (1 g = 64)
 *
 */
/* ===================================================================*/
void ameter_Init();

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
int ameter_getMotion();

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
int ameter_getOrientation();

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
float ameter_X();

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
float ameter_Y();

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
float ameter_Z();

#endif /* AMETER_H_ */
