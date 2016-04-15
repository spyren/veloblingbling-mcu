 /**
 *  @brief
 *      USB CDC serial driver
 *      
 *  Uses the ProcessorExpert USB_CDC_CLASS. 
 *  Some stdio routines (putc, getc, ) for USB CDC serial IO are also defined here. 
 *  Circular buffers instead of streams are used. 
 *  Non blocking write (usb_putc), blocking usb_getc but with timeout.  
 *      
 *  @file
 *      usb.h
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2013-12-04
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

#ifndef USB_H_
#define USB_H_

//#include "types.h"
#include "PE_Types.h"

#define ERR_TIMEOUT         -1
#define ERR_CANCEL          -2

#define  CONTROLLER_ID      (0)   /* ID to identify USB CONTROLLER */ 

#define  KBI_STAT_MASK      (0x0F)

/* ASCII control codes */
/***********************/

#define A_ESC '\x01B'       /**< ASCII Escape code */           
#define A_CR '\x0d'         /**< ASCII Carriage Return code */  
#define A_LF '\x0a'         /**< ASCII Line Feed code */    
#define A_BS '\x08'         /**< ASCII Back Space code */   


#define  DATA_BUFF_SIZE     (16)
#define  RING_BUFF_SIZE_RX	(100)	/**< USB receive buffer size */   
#define  RING_BUFF_SIZE_TX 	(1024)	/**< USB transmit buffer size, big enough for help info */   

extern LDD_TDeviceData* usb_TimerPtr;
extern volatile bool usb_ready;

/* ===================================================================
 *     Method      :  usb_Init
 */
/**
 *  @brief
 *      This function initialises the USB CDC
 */
/* ===================================================================*/
void usb_Init(void);

/* ===================================================================
 *     Method      :  usb_Task
 */
/**
 *  @brief
 *      USB task function. It is called regularly from a timer interrupt
 *
 */
/* ===================================================================*/
void usb_Task(void);

/*  ===================================================================
 *     Method      :  usb_putc
 */
/**     
 *  @brief
 *      standard putc over the USB CDC
 *      
 *  Writes a char to the USB CDC (serial out)
 *  overwrites oldest char if the buffer is full    
 */
/* ===================================================================*/
void usb_putc(uint8_t c); 

/*  ===================================================================
 *     Method      :  usb_getc
 */
/**     
 *  @brief
 *      standard getc over the USB CDC but with timeout
 *      
 *  Reads a char from the USB CDC (serial in). Busy wait until char or 
 *  timeout
 *  
 *  @param
 *      timeout     timeout in x * 10 ms, 0 no timeout
 *  @return
 *      char or -1 for timeout  
 */
/* ===================================================================*/
int usb_getc(int timeout);

/*  ===================================================================
 *     Method      :  usb_puts
 */
/**     
 *  @brief
 *      Write a string s to the USB CDC
 *      
 *  Writes a string to the USB CDC (serial out).    
 */
/* ===================================================================*/
void usb_puts(const char *s);

/*
** ===================================================================
**  Method      :  usb_readline
*/
/** 
 *  @brief      
 *      Reads a line from the USB CDC. ESC abandons edit, BS deletes a char.
 *  @param      
 *      str[out]                string that has been read
 *      length[i]               max. string length
 *  @return
 *      number of chars read
 */
/* ===================================================================*/
int usb_readline(char * str, int length, int timeout);


/*
** ===================================================================
**  Method      :  ltoa
*/
/**
 *  @brief
 *      Prints a 32 bit integer number [-]
 *  @param
 *      str[out]         string with the converted number
 *  @param  
 *      number[in]       long integer number to convert
 */
/* ===================================================================*/
void ltoa(long number, char* str);

/*
** ===================================================================
**  Method      :  itoa2
*/
/**
 *  @brief
 *      Prints a integer number from 00 to 99. 
 *      The boundaries are not checked! 
 *  @param
 *      str[out]         string with the converted number
 *  @param  
 *      number[in]       integer number to convert
 */
/* ===================================================================*/
void itoa2(int z, char* Buffer);

/*
** ===================================================================
**  Method      :  ftoa
*/
/**
 *  @brief
 *      Prints a float number [-]. 
 *      100'000 km = 100'000'000 m -> max 99'999'999.995
 *  @param  
 *      number[in]          float number to convert
 *  @param
 *  	prec[in]			precision 0..2
 *  @param
 *      str[out]            string with the converted number
 *  @return
 *      					-1 for error
 */
/* ===================================================================*/
int ftoa(float number, int prec, char *str);

/*
 ** ===================================================================
 **  Method      :  usb_show_state
 */
/**
 *  @brief
 *      Shows the USB state
 */
/* ===================================================================*/
void usb_show_state();

#endif /* USB_H_ */
