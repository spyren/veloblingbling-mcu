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
 *      wheelsensor.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef WHEELSENSOR_H_
#define WHEELSENSOR_H_

#define WINDOW_LENGTH 126.0			/**< window length 126 � */

#define COLUMN_TIMER_CHANNEL 0		/**< RotTimer Channel number for Column timer */
#define BLING_TIMER_CHANNEL 1		/**< RotTimer Channel number for Bling timer */

extern double circumference;
extern double stretch;

typedef enum {TO_FIRST, IN_FIRST, TO_SECOND, IN_SECOND, NOT_WAITING} wait_modeT;

extern double circumference;	/**< [m] default is road bike with 23 mm pneu  */
extern double stretch;			/**< to stretch the display length */ 
								/*   default is 0.23 m  from hub to the middle of the display */

extern double delay_front;		/**< delay to the first window front wheel 5.0 .. 50.0 � */
extern double between_front;	/**< delay between the windows 10.0 .. 50.0 � */
extern double delay_rear;		/**< delay to the first window read wheel 10.0 .. 50.0 � */
extern double between_rear;		/**< delay between the windows 10.0 .. 50.0 � */

extern bool right;				/**< display on the right side (travel direction) */
extern bool front;				/**< front wheel  */

extern volatile double rotationTime;		/**< [s]  */

extern volatile wait_modeT wait_mode;

extern volatile bool reed_closed;		/**< reed contact closed */

extern volatile bool rotating;			/**< valid rotation */

extern bool enable_bling[2];

extern LDD_TDeviceData* RotTimerPtr;
extern uint16_t rotTimerCh0;
extern uint16_t rotTimerCh1;


/*
** ===================================================================
**  Method      :  wheel_Init
*/
/**
 *  @brief
 *  	Initialises the counters
 */
/* ===================================================================*/
void wheel_Init(); 

/*
** ===================================================================
**  Method      :  wheel_Synch
*/
/**
 *  @brief
 *  	Interrupt from reed contact to synchronise the wheel
 *  	
 *  	Measures the rotation time. 
 *  	Blind for the first 5 ms (debouncing).
 *  	Has to be between MIN_T and MAX_T 
 */
/* ===================================================================*/
void wheel_Synch();

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
void wheel_TimerOverrun();

/*
** ===================================================================
**  Method      :  wheel_StartColumn
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (restart counter)
 */
/* ===================================================================*/
void wheel_StartColumn();

/*
** ===================================================================
**  Method      :  wheel_checkReed
*/
/**
 *  @brief
 *  	Check the reed contact
 *  	It is called regularly from a timer interrupt (every 500 us)
 *  	
 */
/* ===================================================================*/
void wheel_checkReed() ;

#endif /* WHEELSENSOR_H_ */
