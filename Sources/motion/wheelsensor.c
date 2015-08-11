/**
 *  @brief
 *      Wheel rotation related stuff e.g. timing (synchronisation) for display column
 *      Wheel synchronisation.
 *      
 *      v_max = 70 km/h = 19.44 m/s -> 20 m/s
 *      v_min = 15 km/h = 4.16 m/s  ->  4 m/s
 *      v_min = 10 km/h = 4.16 m/s  ->  2.8 m/s
 *      
 *      C = 2.105 m   ; 28" race wheel (2.133 m wikipedia)
 *      
 *      t_min = C / v_max = 0.109 s (0.0758)
 *      t_max = C / v_min = 0.505 s (0.758)
 *      
 *      a_r = v� / r = 
 *        46 .. 1200 m/s^2 (am äussersten Punkt, d.h. auf dem Pneu)
 *        4.7 .. 122 g
 *        7.9 .. 197 m/s^2 (bei etwa 0.05 m von Nabe entfernt)
 *        0.8 .. 20 g
 *        3.2 .. 79 m/s^2  (bei etwa 0.02 m von Nabe entfernt)
 *        0.3 .. 8 g
 *        
 *		distance diode to diode = 5.12 mm
 *		display-length = 63 * 5.12 mm = 322.56 mm 
 *		               = 99 * 5.12 mm = 506.88 mm
 *		C_LED = 2 * Pi * 0.23 m = 1.445 m
 *
 *      Phi_segment = display-length / C_LED * 2 Pi = 0.2232 * 2 * Pi = 80°
 *		    = 0.351 * 2 * Pi = 126°
 *      
 *      t_column_min = (0.2232 * t_min) / 99 = 386 us (269 us) -> about 20 kHz PWM
 *      t_column_max = (0.2232 * t_max) / 99 = 1.78 ms
 *      
 *      stretch = 0.8 .. 1.2 
 *      
 *      Front wheel:
 *      first top window
 *      Right side -> started with first column on top window, started with last column on bottom window
 *      Left side  -> started with last column on top window, started with first column on bottom window
 *      
 *      Rear wheel:
 *      first bottom window
 *      
 *  @file
 *      wheelsensor.c
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
 **  @defgroup wheelsensor_module Wheel sensor module
 **  @{
 */         
/* MODULE wheel sensor*/

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

// PE include files
// ****************
#include "PE_Types.h"
#include "RotTimer.h"
#include "ReedContact.h"

// application include files
// *************************
#include "definitions.h"
#include "wheelsensor.h"
#include "cyclo/cyclocomputer.h"
#include "hmi/mode.h"
#include "visual/led.h"
#include "visual/display.h"
#include "comm/usb.h"
#include "bling.h"
#include "powermgr.h"

#define TIMER_TICK (1.0/375000.0)	/* counter frequency is 375 kHz -> tick 2.667 us */ 
//#define T_MAX 189375				/* maximum time for rotation: 0.505 s -> 505'000 / 2.667 = 189'375 */
#define T_MAX 284175				/* maximum time for rotation (10 km/h): 0.758 s -> 758'000 / 2.667 = 284'175 */
#define T_MIN 28417					/* minimum time for rotation (100 km/h): 0.0758 s -> 75'800 / 2.667 = 28'417 */

#define MAX_TURNS 5					/* 5 * 175 ms = 800 ms */

#define DEBOUNCE_TIME 1500			/* 4 ms -> 4000 / 2.667 = 1500, at 100 km/h about 19 � */
#define DEBOUNCE_TIME_S 0.004

#define FRONT_LIGHT_DELAY 60.0
#define REAR_LIGHT_DELAY 80.0


// Global Variables
// ****************
double circumference = 2.105;		/**< [m] default is road bike with 23 mm tire  */
double stretch = 1.0;				/**< to stretch the display length */ 
/*   default is 0.23 m  from hub to the middle of the display */

double delay_front = 5.0;			/**< delay to the first window front wheel 5.0 .. 50.0 � */
double between_front = 20.0;		/**< delay between the windows 10.0 .. 50.0 � */
double delay_rear = 10.0;			/**< delay to the first window read wheel 5.0 .. 50.0 � */
double between_rear = 40.0;			/**< delay between the windows 10.0 .. 50.0 � */

bool right = FALSE;					/**< display on the right side (travel direction) */
bool front = FALSE; 				/**< front wheel  */

volatile double rotationTime = 0.0;			/**< [s]  */

volatile wait_modeT wait_mode = NOT_WAITING;

volatile bool reed_closed = FALSE;			/**< reed contact closed */

volatile bool rotating = FALSE;				/* valid rotation */

bool enable_bling[2] = {FALSE, FALSE};

LDD_TDeviceData* RotTimerPtr;
uint16_t rotTimerCh0;
uint16_t rotTimerCh1;

// Local Variables
// ***************
static volatile uint8_t timerTurns;			/* Timer overrun after 174.763 ms */

static volatile int16_t currColumn = 0;
static volatile int16_t firstColumn;
static volatile int16_t endColumn;

uint16_t columnPeriodTicks;


/*
 ** ===================================================================
 **  Method      :  wheel_Init
 */
/**
 *  @brief
 *  	Initialises the counters
 */
/* ===================================================================*/
void wheel_Init() {
	RotTimerPtr = RotTimer_Init(NULL);
}

/*
 ** ===================================================================
 **  Method      :  wheel_Synch
 */
/**
 *  @brief
 *  	Interrupt from reed contact (hall sensor) to synchronise the wheel
 *  	
 *  	Measures the rotation time. 
 *  	Blind for the first 5 ms (debouncing).
 *  	Has to be between MIN_T and MAX_T 
 */
/* ===================================================================*/
void wheel_Synch() {
	uint32_t rotationTimeU;
	double delay;
	
	if (tripMode == TRIP_PAUSED) {
		tripMode = TRIP_STARTED;
	}

	trip_timeout = 0;

	sleep_wakeup = TRUE;

	if (rotating) {
		rotationTimeU = (uint32_t) RotTimer_GetCounterValue(RotTimerPtr);
		rotationTimeU = rotationTimeU + ((uint32_t) timerTurns << 16);
		if (rotationTimeU < DEBOUNCE_TIME) {
			return;
		}

		// restart rotation timer
		timerTurns = 0;
		// RotTimer_Disable(RotTimerPtr);
		RotTimer_ResetCounter(RotTimerPtr);
		// RotTimer_GetEventStatus(RotTimerPtr);
		// RotTimer_Enable(RotTimerPtr);

		/* calculate rotation time */
		rotationTime = rotationTimeU * TIMER_TICK;

		/* valid rotation for cyclocomputer */
		cyclo_Information(); 		

		if (low_energy) {
			return;
		}

		if ( (rotationTimeU < T_MIN) || (rotationTimeU > T_MAX) ) {
			/* to fast or to slow */
			rotating = FALSE;
			wait_mode = NOT_WAITING;
			RotTimer_Disable(RotTimerPtr);
			enable_bling[TOPSIDE] = FALSE;
			enable_bling[BOTTOMSIDE] = FALSE;
			bling_StopTimer();
		} else {
			/* start timer for first window */
			wait_mode = TO_FIRST;
			if (front) {
				if (displayMode[TOPSIDE][UPPER] == LIGHT) {
					delay = FRONT_LIGHT_DELAY;
				} else {
					delay = delay_front;
				}
			} else {
				if (displayMode[TOPSIDE][UPPER] == LIGHT) {
					delay = REAR_LIGHT_DELAY;
				} else {
					delay = delay_rear;
				}	
			}
			

			// set time (delay) for the first window
			uint16_t periodTicks = (rotationTime * (delay / 360.0)) / TIMER_TICK;
			RotTimer_SetOffsetTicks(RotTimerPtr, COLUMN_TIMER_CHANNEL, periodTicks);

			// calculate timer ticks for columns
			columnPeriodTicks = rotationTime * (WINDOW_LENGTH / (360.0 * MAX_COLUMN)) / TIMER_TICK;

			enable_bling[TOPSIDE] = TRUE;
			enable_bling[BOTTOMSIDE] = TRUE;

			bling_StartTimer();
		}

	} else {
		// not rotating -> start measurement
		if (!standby) {
			timerTurns = 0;
			// RotTimer_Disable(RotTimerPtr);
			RotTimer_ResetCounter(RotTimerPtr);
			// RotTimer_GetEventStatus(RotTimerPtr);
			RotTimer_Enable(RotTimerPtr);
			rotating = TRUE;
			bling_StopTimer();
		}
		rotationTime = -1.0;
		
		/* valid rotation for cyclocomputer */
		cyclo_Information(); 	
		
		if (!low_energy) {
			// show reed contact closed
			set_led(TOPSIDE, LED16, GREEN);
			write_ledColumn(TOPSIDE);
			reed_closed = TRUE;
		}

	}
}

/*
 ** ===================================================================
 **  Method      :  wheel_TimerOverrun
 */
/**
 *  @brief
 *  	Interrupt timer overrun from RotTimer
 *  	
 *  	Counts the turns up because the timer period is to short
 */
/* ===================================================================*/
void wheel_TimerOverrun() {
	if (++timerTurns >= MAX_TURNS) {
		// 
		rotating = FALSE;
		wait_mode = NOT_WAITING;
		RotTimer_Disable(RotTimerPtr);
		bling_StopTimer();
		rotationTime = -1.0;
		enable_bling[TOPSIDE] = FALSE;
		enable_bling[BOTTOMSIDE] = FALSE;
	}
}


/*
** ===================================================================
**  Method      :  wheel_StartColumn
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (Channel 0 RotTimer/FTM0), reset channel offset
 */
/* ===================================================================*/
void wheel_StartColumn() {
	bool finished = FALSE;
	uint16_t periodOffset;
	
	windowT window;
	
	switch (wait_mode) {
	case TO_FIRST:
		if (front) {
			// front wheel -> top window is first
			window = UPPER;
			if (right) {
				// display from the beginning
				currColumn = 0;
				endColumn = display[TOPSIDE][UPPER].length;
			} else {
				// display from back
				currColumn = MAX_COLUMN - 1;
				firstColumn = currColumn - display[BOTTOMSIDE][UPPER].length;
			}
		} else {
			// rear wheel -> bottom window is first
			window = LOWER;
			if (!right) {
				// display from the beginning
				currColumn = 0;
				endColumn = display[BOTTOMSIDE][LOWER].length;
			} else {
				// display from back
				currColumn = MAX_COLUMN - 1;
				firstColumn = currColumn - display[TOPSIDE][UPPER].length;
			}
		}
		display_column(window, currColumn);	
		
		periodOffset = rotTimerCh0 + columnPeriodTicks;
		RotTimer_SetOffsetTicks(RotTimerPtr, COLUMN_TIMER_CHANNEL, periodOffset);
		
		wait_mode = IN_FIRST;
		break;
	case IN_FIRST:
		if (front) {
			// front wheel -> top window is first 
			window = UPPER;
			if (right) {
				// display from the beginning
				if (++currColumn >= MAX_COLUMN) {
					finished = TRUE;
				}
			} else {
				// display from back
				if (--currColumn < 0 ) {
					finished = TRUE;
				}
			}	
		} else {
			// rear wheel -> bottom window is first
			window = LOWER;
			if (! right) {
				// display from the beginning
				if (++currColumn >= MAX_COLUMN) {
					finished = TRUE;
				}
			} else {
				// display from back
				if (--currColumn < 0 ) {
					finished = TRUE;
				}
			}	
		}
		if (finished) {
			// set time (delay between) for the second window
			if (front) {
				periodOffset = rotTimerCh0 + (rotationTime * (between_front / 360.0)) / TIMER_TICK;
			} else {
				periodOffset = rotTimerCh0 + (rotationTime * (between_rear / 360.0)) / TIMER_TICK;
			}
			RotTimer_SetOffsetTicks(RotTimerPtr, COLUMN_TIMER_CHANNEL, periodOffset);
			
			clear_leds(TOPSIDE);
			write_ledColumn(TOPSIDE);
			wait_ledColumn();
			clear_leds(BOTTOMSIDE);
			write_ledColumn(BOTTOMSIDE);
			wait_ledColumn();			
			wait_mode = TO_SECOND;
			if (displayMode[TOPSIDE][UPPER] == LIGHT) {
				wait_mode = NOT_WAITING;
			}
			enable_bling[TOPSIDE] = TRUE;
			enable_bling[BOTTOMSIDE] = TRUE;

		} else {
			display_column(window, currColumn);	

			// timeout for the next column
			periodOffset = rotTimerCh0 + columnPeriodTicks;
			RotTimer_SetOffsetTicks(RotTimerPtr, COLUMN_TIMER_CHANNEL, periodOffset);
		}
		break;
	case TO_SECOND:
		if (front) {
			// front wheel -> bottom window is second
			window = LOWER;
			if (! right) {
				// display from the beginning
				currColumn = 0;
			} else {
				// display from back
				currColumn = MAX_COLUMN - 1;
			}
		} else {
			// rear wheel -> top window is second
			window = UPPER;
			if (right) {
				// display from the beginning
				currColumn = 0;
			} else {
				// display from back
				currColumn = MAX_COLUMN - 1;
			}
		}
		display_column(window, currColumn);	
		
		// timeout for the next column
		periodOffset = rotTimerCh0 + columnPeriodTicks;
		RotTimer_SetOffsetTicks(RotTimerPtr, COLUMN_TIMER_CHANNEL, periodOffset);
	
		wait_mode = IN_SECOND;
		break;
	case IN_SECOND:
		if (front) {
			// front wheel -> bottom window is second
			window = LOWER;
			if (! right) {
				// display from the beginning
				if (++currColumn >= MAX_COLUMN) {
					finished = TRUE;
				}
			} else {
				// display from back
				if (--currColumn < 0 ) {
					finished = TRUE;
				}
			}	
		} else {
			// rear wheel -> top window is second
			window = UPPER;
			if (right) {
				// display from the beginning
				if (++currColumn >= MAX_COLUMN) {
					finished = TRUE;
				}
			} else {
				// display from back
				if (--currColumn < 0 ) {
					finished = TRUE;
				}
			}	
		}
		if (finished) {
			RotTimer_SetOffsetTicks(RotTimerPtr, COLUMN_TIMER_CHANNEL, 0xffff);
			
			clear_leds(TOPSIDE);
			write_ledColumn(TOPSIDE);
			wait_ledColumn();
			clear_leds(BOTTOMSIDE);
			write_ledColumn(BOTTOMSIDE);
			wait_ledColumn();			
			wait_mode = NOT_WAITING;

			enable_bling[TOPSIDE] = TRUE;
			enable_bling[BOTTOMSIDE] = TRUE;
		} else {
			display_column(window, currColumn);		
			
			// timeout for the next column
			periodOffset = rotTimerCh0 + columnPeriodTicks;
			RotTimer_SetOffsetTicks(RotTimerPtr, COLUMN_TIMER_CHANNEL, periodOffset);
		}
		break;
	case NOT_WAITING:
		break;
	}
}


/*
** ===================================================================
**  Method      :  wheel_checkReed
*/
/**
 *  @brief
 *  	Check the reed contact
 *  	It is called regularly from the tick timer interrupt (every 20 ms)
 *  	
 */
/* ===================================================================*/
void wheel_checkReed() {
	if (reed_closed) {
		if (ReedContact_GetVal(NULL)) {
			set_led(TOPSIDE, LED16, BLACK);
			write_ledColumn(TOPSIDE);
			reed_closed = FALSE;
		}

	}
}


/**
 ** @}
 */


