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
 *      usb.c
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

/**
 **  @addtogroup usb_module USB module documentation
 **  @{
 */         

// system include files
// ********************
/* Include the derivative-specific header file */
#include <IO_Map.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// PE include files
// ****************
#include "usb_cdc.h"        /* USB CDC Class Header File */
#include "USBpoll.h"

// application include files
// *************************
#include "definitions.h"
#include "usb.h"
#include "powermgr.h"
#include "visual/led.h"


// Local Types
// ***********

/* Opaque buffer element type. */
typedef struct { uint8_t value; } ElemType;

/* Circular buffer object */
typedef struct {
    int         size;       /* maximum number of elements           */
    int         start;      /* index of oldest element              */
    int         end;        /* index at which to write new element  */
    ElemType    *elems;     /* array of elements                    */
} CircularBuffer;



// Local Functions Prototypes
// **************************

static void usb_cdc_Callback(uint8_t controller_ID,
        uint8_t event_type, void* val);
static void usb_Notify_Callback(uint8_t controller_ID,
        uint8_t event_type, void* val);


// Local Variables
// ***************

/* Virtual COM Application Carrier Activate Flag */
static volatile boolean start_transactions = FALSE;
static volatile boolean readyToSend = TRUE;

static CircularBuffer cbRxBuffer;
static CircularBuffer cbTxBuffer;

static ElemType cbRxBuffer_a[RING_BUFF_SIZE_RX + 1];
static ElemType cbTxBuffer_a[RING_BUFF_SIZE_TX + 1];


// Global Variables
// ****************
LDD_TDeviceData* usb_TimerPtr;

/* Virtual COM Application start Init Flag */
volatile bool usb_ready = FALSE;

/*****************************************************************************
* Public Functions
*****************************************************************************/

/* ===================================================================
 *     Method      :  cbInit
 */
/**
 *   @brief
 *      Initialises the circular buffer. 
 *   @see
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *   @param
 *      cb          circular buffer structure
 *   @param
 *      size        buffer size (real buffer is one element bigger)
 *   @param
 *      elements    pointer to the buffer
 */
/* ===================================================================*/
void cbInit(CircularBuffer *cb, int size,  ElemType *elements) {
    cb->size  = size + 1; /* include empty elem */
    cb->start = 0;
    cb->end   = 0;
    cb->elems = elements;
}
 
//void cbFree(CircularBuffer *cb) {
//    free(cb->elems); /* OK if null */ }


/* ===================================================================
 *     Method      :  cbIsFull
 */
/**
 *   @brief
 *      Is the circular buffer full?
 *   @see
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *   @param
 *      cb          circular buffer structure
 *   @return
 *      TRUE if full
 */
/* ===================================================================*/
int cbIsFull(CircularBuffer *cb) {
    return (cb->end + 1) % cb->size == cb->start; }


/* ===================================================================
 *     Method      :  cbIsEmpty
 */
/**
 *   @brief
 *      Is the circular buffer empty?
 *   @see
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *   @param
 *      cb          circular buffer structure
 *   @return
 *      TRUE if empty
 */
/* ===================================================================*/
int cbIsEmpty(CircularBuffer *cb) {
    return cb->end == cb->start; }


/* ===================================================================
 *     Method      :  cbWrite
 */
/**
 *   @brief
 *      Write an element to the circular buffer. 
 *      
 *   Write an element, overwriting oldest element if buffer is full. 
 *   App can choose to avoid the overwrite by checking cbIsFull().
 *   
 *   @see
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *   @param
 *      cb          circular buffer structure
 *   @param
 *      elem        element
 */
/* ===================================================================*/
void cbWrite(CircularBuffer *cb, ElemType  *elem) {
    cb->elems[cb->end] = *elem;
    cb->end = (cb->end + 1) % cb->size;
    if (cb->end == cb->start)
        cb->start = (cb->start + 1) % cb->size; /* full, overwrite */
}


/* ===================================================================
 *     Method      :  cbRead
 */
/**
 *   @brief
 *      Read an element from the circular buffer. 
 *      
 *   Read oldest element. App must ensure !cbIsEmpty() first. 
 *   
 *   @see
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *   @param
 *      cb          circular buffer structure
 *   @param
 *      elem        element
 */
/* ===================================================================*/
void cbRead(CircularBuffer *cb, ElemType  *elem) {
    *elem = cb->elems[cb->start];
    cb->start = (cb->start + 1) % cb->size;
}
 

/* ===================================================================
 *     Method      :  usb_Init
 */
/**
 *   @brief
 *      This function initialises the USB CDC
 */
/* ===================================================================*/
void usb_Init(void)
{
    uint8_t   error;

    // Initialise the USB circular buffers
    cbInit(&cbRxBuffer, RING_BUFF_SIZE_RX, cbRxBuffer_a);
    cbInit(&cbTxBuffer, RING_BUFF_SIZE_TX, cbTxBuffer_a);

    usb_TimerPtr = USBpoll_Init(NULL);
    
    //DisableInterrupts;
    /* Initialize the USB interface */
    Cpu_DisableInt();
    error = USB_Class_CDC_Init(CONTROLLER_ID, usb_cdc_Callback,
            NULL, usb_Notify_Callback);
    Cpu_EnableInt();
    if (error != USB_OK) {
        /* Error initializing USB-CDC Class */
        // LED_Error_ClrVal(NULL);
        return;
    }
    //EnableInterrupts;
    /* delay for a while */
    wait_10ms(2);
    
    /* Queue next receive */
    (void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, NULL, 0);

    USBpoll_Enable(usb_TimerPtr);
}


/* ===================================================================
 *     Method      :  usb_Task
 */
/**
 *   @brief
 *      USB task function. It is called regularly from a timer interrupt
 *
 */
/* ===================================================================*/
void usb_Task(void) {
    static ElemType element;
    int status;

    /* call the periodic task function */
    USB_Class_CDC_Periodic_Task();

    /*check whether enumeration is complete or not */
    if ((usb_ready==TRUE) && (start_transactions==TRUE)) {

        if (readyToSend) {
            if (! cbIsEmpty(&cbTxBuffer)) {
                cbRead(&cbTxBuffer, &element);

                status = USB_Class_CDC_Interface_DIC_Send_Data(CONTROLLER_ID, &element.value, 1);
                if (status != USB_OK) {
                    /* Send Data Error Handling Code goes here */
                    //LED_Error_ClrVal(NULL);
                }
                
                readyToSend = FALSE;
            }
        }
    }
}


/*  ===================================================================
 *     Method      :  usb_cdc_Callback
 */
/**     
 *  @brief
 *      This function handles CDC Class callback
 *      
 *  This function is called from the cdc class layer whenever reset occurs or enum
 *  is complete. After the enum is complete this function sets a variable so
 *  that the application can start.
 *  This function also receives DATA Send and RECEIVED Events
 * 
 *  @param       
 *      controller_ID    : Controller ID
 *  @param       
 *      event_type       : Value of the event
 *  @param       
 *      val              : gives the configuration value
 */
/* ===================================================================*/
static void usb_cdc_Callback (uint8_t controller_ID, uint8_t event_type, void* val) {
    (void) controller_ID;       //unused
    (void) val;                 //unused
    
    if (event_type == USB_APP_BUS_RESET) {
        usb_ready=FALSE;
    } else if (event_type == USB_APP_ENUM_COMPLETE) {
        usb_ready=TRUE;
    } else if (event_type == USB_APP_DATA_RECEIVED) {
        /* Copy Received Data buffer to ring Buffer */
        USB_PACKET_SIZE BytesToBeCopied;
        APP_DATA_STRUCT* dp_rcv = (APP_DATA_STRUCT*)val;
        uint8_t usb_index;
        ElemType element;
        BytesToBeCopied = (USB_PACKET_SIZE)((dp_rcv->data_size > DATA_BUFF_SIZE) ?
                DATA_BUFF_SIZE:dp_rcv->data_size);
        for (usb_index = 0; usb_index<BytesToBeCopied ; usb_index++) {
            element.value = dp_rcv->data_ptr[usb_index];
            cbWrite(&cbRxBuffer, &element);
        }
        /* Queue next receive */
        (void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, NULL, 0);
        //sleep_wakeup = TRUE;
    } else if (event_type == USB_APP_SEND_COMPLETE) {
        readyToSend = TRUE;
//    } else if (event_type == USB_APP_EP_UNSTALLED) {
//    	usb_ready=FALSE;
//    	start_transactions = FALSE;
//    } else if (event_type == USB_APP_CONFIG_CHANGED) {
//    	usb_ready=FALSE;
//    	start_transactions = FALSE;
//
//    } else if (event_type == USB_APP_ERROR) {
//    	usb_ready=FALSE;
//    	start_transactions = FALSE;
//    } else if (event_type == USB_APP_GET_DATA_BUFF) {
//
//    } else if (event_type == USB_APP_EP_STALLED) {
//    	usb_ready=FALSE;
//    	start_transactions = FALSE;
//
//    } else {
//    	// all other events
////    	usb_ready=FALSE;
////    	start_transactions = FALSE;
//
    }
    
    sleep_wakeup = TRUE;
    return;
}


/*  ===================================================================
 *     Method      :  usb_Notify_Callback
 */
/**     
 *  @brief
 *      This function handles PSTN Sub Class callbacks
 *      
 * This function handles USB_APP_CDC_CARRIER_ACTIVATED and
 * USB_APP_CDC_CARRIER_DEACTIVATED PSTN Events
 * 
 *  @param       
 *      controller_ID    : Controller ID
 *  @param       
 *      event_type       : PSTN Event Type
 *  @param       
 *      val              : gives the configuration value
 */
/* ===================================================================*/
static void usb_Notify_Callback (
        uint8_t controller_ID,   /* [IN] Controller ID */
        uint8_t event_type,      /* [IN] PSTN Event Type */
        void* val               /* [IN] gives the configuration value */
)
{
    (void) controller_ID;       //unused
    (void) val;                 //unused
    if(usb_ready == TRUE)
    {
        if (event_type == USB_APP_CDC_CARRIER_ACTIVATED) {
            start_transactions = TRUE;
        }
        else if (event_type == USB_APP_CDC_CARRIER_DEACTIVATED) {
            start_transactions = FALSE;
        }
    }
    return;
}


/*  ===================================================================
 *     Method      :  usb_putc
 */
/**     
 *  @brief
 *      standard putc over the USB CDC
 *      
 *  Writes a char to the USB CDC (serial out)
 *  overwrites oldest char if the buffer is full (non blocking write)   
 */
/* ===================================================================*/
void usb_putc(uint8_t c) {
    ElemType element;
    
    element.value = c;
    cbWrite(&cbTxBuffer, &element);
}


/*  ===================================================================
 *     Method      :  usb_getc
 */
/**     
 *  @brief
 *      standard getc over the USB CDC but with timeout
 *      
 *  Reads a char from the USB CDC (serial in). Busy wait until char or 
 *  timeout (blocking read).
 *  
 *  @param
 *      timeout     timeout in x * 10 ms, 0 no timeout
 *  @return
 *      char or -1 (ERR_TIMEOUT) for timeout  
 */
/* ===================================================================*/
int usb_getc(int timeout) {
    ElemType element;
    int time = 0;

    while(cbIsEmpty(&cbRxBuffer)) {
        // wait for a char      
        wait_10ms(1);
        if (timeout != 0) {
            // there is a timeout
            if (time++ > timeout)
                // timeout
                return ERR_TIMEOUT;
        }
    }
    cbRead(&cbRxBuffer, &element);
    return (int) element.value;
}


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
void usb_puts(const char *s) {
    int i;
    for (i=0; i < strlen(s); i++) {
        if (s[i] == A_LF) {
            usb_putc(A_CR);
            usb_putc(A_LF);
        } else {
            usb_putc(s[i]);
        }
    }
}


/*
 * ===================================================================
 *  Method      :  usb_readline
*/
/** 
 *  @brief      
 *      Reads a line from the USB CDC. ESC abandons edit, BS deletes a char.
 *  @param      
 *      str[out]                string that has been read
 *  @param  
 *      length[in]              max. string length
 *  @param      
 *      timeout[in]             timeout in [ms]
 *  @return
 *      number of chars read
 */
/* ===================================================================*/
int usb_readline(char * str, int length, int timeout ) {
    int C;
    int i = 0;
    
    strcpy(str, "");
    while (1) {
        C = usb_getc(timeout);
        if (C == ERR_TIMEOUT) {
            return ERR_TIMEOUT;
        } 
        else if (C < 32) {
            // Control character
            if (C == A_CR || C == '\n') {
                str[i] = 0;
                break;
            }
            else if (C == A_BS) {
                if (i > 0) {
                    i--;
                    usb_putc(A_BS);
                    usb_putc(' ');
                    usb_putc(A_BS);
                }
            }
            else if (C == A_ESC) {
                strcpy(str, "");
                i = ERR_CANCEL;
                break;
            }
        }
        else {
            // character
            usb_putc(C);        // echo character
            str[i] = C;
            i++;
        }
        if (i >= length) {
            str[i] = 0;
            break;
        }

    }
    return i;
}



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
void ltoa(long number, char* str) {
    int i = 0;
    int j;
    char tmp;
    unsigned long u;   
    
    if (number < 0 ) {
        str[0] = '-';
        str++;
        u = labs(number); 
    } else { 
        u = (unsigned long)number;
    }
    do {
        str[i++] = '0' + u % 10;
        u /= 10;
    } while( u > 0 );
    for (j = 0; j < i / 2; ++j ) {
        tmp = str[j];
        str[j] = str[i-j-1];
        str[i-j-1] = tmp;
    }
    str[i] = '\0';
}

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
void itoa2(int number, char* str) {
	
	ltoa((long)number, str);
	if (strlen(str) == 1) {
		str[1] = str[0];
		str[2] = 0;
		str[0] = '0';
	}
}


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
int ftoa(float number, int prec, char *str) {
    char fract[5];
    int64_t num;
    int mult = 1;
    
    if ( (number > 99999999.995 || number < -999999999.995) || (prec < 0 || prec > 2) ) {
        strcpy(str, "NaN");
        return -1;
    }
    
    // round
    if (prec == 1) {
    	mult = 10;
    } else if (prec == 2) {
    	mult = 100;
    }
    
    if (number >= 0) {
    	num = (int64_t)(floor(mult * number + 0.5));
    }
    else {
    	num = (int64_t)(ceil(mult * number - 0.5));
    	str[0] = '-';
    	str++;
    }

    if (prec == 0) {
    	ltoa((long int) num, str);
    } else {
    	ltoa(labs ((long int) num/mult), str);
    	strcat(str, ".");
    	if (prec == 1) {
    		ltoa(labs((long int) num%mult), fract);
    	} else {
    		itoa2(labs((long int) num%mult), fract);
    	}
    	strcat(str, fract);
    }
    return 0;
}


/*
 ** ===================================================================
 **  Method      :  usb_show_state
 */
/**
 *  @brief
 *      Shows the USB state
 */
/* ===================================================================*/
void usb_show_state() {

#ifdef USB_VOLTAGE_DETECTION
	if (UsbSupply_GetVal()) {
		if (usb_ready) {
			// USB is connected
			if (start_transactions) {
				// CDC ready
				set_led(TOPSIDE, LED14, GREEN);
			} else {
				set_led(TOPSIDE, LED14, YELLOW);
			}
		} else {
			// only an USB charger
			set_led(TOPSIDE, LED14, RED);
		}
	} else {
		// USB not connected
		set_led(TOPSIDE, LED14, BLACK);
	}
#endif

}






/*!
** @}
*/
