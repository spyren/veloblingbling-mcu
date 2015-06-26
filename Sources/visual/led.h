/**
 *  @brief
 *      LED driver. It is a row with 12 multicolor LEDs 
 *      (RGB red, green, and blue)
 *
 *  @file
 *      led.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2013-12-04
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */


#ifndef LED_H_
#define LED_H_

/** 16 LEDs */
typedef enum {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15, LED16} LED_nrT;

/** lowest (first) bit red, second green, third blue */ 
typedef enum {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE} LED_colorT; 


typedef enum {TOPSIDE, BOTTOMSIDE} surfaceT;

#define RED_MASK 	0x01
#define GREEN_MASK 	0x02
#define BLUE_MASK 	0x04

volatile bool Led_BlockSent;

/*
 ** ===================================================================
 **  Method      :  led_Init
 */
/**
 *  @brief
 *  	Initialises the SPI and clears all LEDs
 */
/* ===================================================================*/
void led_Init();

/*
 ** ===================================================================
 **  Method      :  clear_leds
 */
/**
 *  @brief
 *  	clear all LEDs
  *  @param
 *  	surface	top- or bottomside	
 */
/* ===================================================================*/
void clear_leds(surfaceT surface);

/*
 ** ===================================================================
 **  Method      :  set_led
 */
/**
 *  @brief
 *  	Sets the three LEDs in the multicolor LED according to the specified color
 *  @param
 *  	surface	top- or bottomside
 *  @param
 *      nr  	the LED number (row), from LED1 to LED12
 *  @param
 *      color	the LED color BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE
 *        	
 */
/* ===================================================================*/
void set_led(surfaceT surface, LED_nrT nr, LED_colorT color);

/*
 ** ===================================================================
 **  Method      :  set_ledColumn
 */
/**
 *  @brief
 *  	Sets a LED column
 *  @param
 *  	surface	top- or bottomside
 *  @param
 *      column	the lower 48 bits are the LEDs
 */
/* ===================================================================*/
void set_ledColumn(surfaceT surface, uint64_t column);

/*
 ** ===================================================================
 **  Method      :  write_ledColumn
 */
/**
 *  @brief
 *  	Writes all LEDs in a column to the SPI
 *  @param
 *  	surface		surface
 */
/* ===================================================================*/
void write_ledColumn(surfaceT surface);

/*
 ** ===================================================================
 **  Method      :  wait_ledColumn
 */
/**
 *  @brief
 *  	Waits till the column us written to the SPI
 */
/* ===================================================================*/
void wait_ledColumn(); 

#endif /* LED_H_ */


