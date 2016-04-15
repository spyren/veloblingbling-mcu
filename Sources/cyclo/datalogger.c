/**
 *  @brief
 *      Logs (e.g. every minute) the data to the Flash memory.
 *      Log records = 64 kiB / 12 Bytes = 5'400
 *      Log intervall 60 s -> log time = 90 h 
 *                    10 s ->            15 h 
 *                     5 s ->             7.5 h
 *      
 *      Log Record
 *      	trip distance
 *      	altitude
 *      	temperature
 *      	
 *      Log Header
 *      	starttime
 *      	intervall
 *      
 *  @file
 *      datalogger.c
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
 **  @defgroup datalogger_module Datalogger module
 **  @{
 */         
/* MODULE Datalogger */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

// PE include files
// ****************
#include "PE_Types.h"

// application include files
// *************************
#include "definitions.h"
#include "comm/usb.h"
#include "motion/wheelsensor.h"

// Global Variables
// ****************
double logIntervall = 60.0; 		/**< data log intervall [s] */

// Local Variables
// ***************


/**
 ** @}
 */


