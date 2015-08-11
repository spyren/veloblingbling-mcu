/**
 *  @brief
 *      Tests the hardware
 *      
 *  @file
 *      test.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-07
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

/**
 **  @defgroup mode_module Mode module
 **  @{
 */         
/* MODULE mode */

// system include files
// ********************
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

// PE include files
// ****************
#include "Cpu.h"

// application include files
// *************************
#include "definitions.h"
#include "powermgr.h"
#include "hmi/cli.h"
#include "hmi/button.h"
#include "visual/led.h"
#include "comm/usb.h"


#define TEST_STEPS 96

struct step_s {
	LED_nrT    nr; 
	LED_colorT color;
	surfaceT surface;
	char 	   text[30];
};

static const struct step_s steps_a[TEST_STEPS] = {
		{LED1,  RED,   TOPSIDE, "LED1  red, top\n"},
		{LED1,  GREEN, TOPSIDE, "LED1  green, top\n"},
		{LED1,  BLUE,  TOPSIDE, "LED1  blue, top\n"},
		{LED2,  RED,   TOPSIDE, "LED2  red, top\n"},
		{LED2,  GREEN, TOPSIDE, "LED2  green, top\n"},
		{LED2,  BLUE,  TOPSIDE, "LED2  blue, top\n"},
		{LED3,  RED,   TOPSIDE, "LED3  red, top\n"},
		{LED3,  GREEN, TOPSIDE, "LED3  green, top\n"},
		{LED3,  BLUE,  TOPSIDE, "LED3  blue, top\n"},
		{LED4,  RED,   TOPSIDE, "LED4  red, top\n"},
		{LED4,  GREEN, TOPSIDE, "LED4  green, top\n"},
		{LED4,  BLUE,  TOPSIDE, "LED4  blue, top\n"},
		{LED5,  RED,   TOPSIDE, "LED5  red, top\n"},
		{LED5,  GREEN, TOPSIDE, "LED5  green, top\n"},
		{LED5,  BLUE,  TOPSIDE, "LED5  blue, top\n"},
		{LED6,  RED,   TOPSIDE, "LED6  red, top\n"},
		{LED6,  GREEN, TOPSIDE, "LED6  green, top\n"},
		{LED6,  BLUE,  TOPSIDE, "LED6  blue, top\n"},
		{LED7,  RED,   TOPSIDE, "LED7  red, top\n"},
		{LED7,  GREEN, TOPSIDE, "LED7  green, top\n"},
		{LED7,  BLUE,  TOPSIDE, "LED7  blue, top\n"},
		{LED8,  RED,   TOPSIDE, "LED8  red, top\n"},
		{LED8,  GREEN, TOPSIDE, "LED8  green, top\n"},
		{LED8,  BLUE,  TOPSIDE, "LED8  blue, top\n"},
		{LED9,  RED,   TOPSIDE, "LED9  red, top\n"},
		{LED9,  GREEN, TOPSIDE, "LED9  green, top\n"},
		{LED9,  BLUE,  TOPSIDE, "LED9  blue, top\n"},
		{LED10, RED,   TOPSIDE, "LED10 red, top\n"},
		{LED10, GREEN, TOPSIDE, "LED10 green, top\n"},
		{LED10, BLUE,  TOPSIDE, "LED10 blue, top\n"},
		{LED11, RED,   TOPSIDE, "LED11 red, top\n"},
		{LED11, GREEN, TOPSIDE, "LED11 green, top\n"},
		{LED11, BLUE,  TOPSIDE, "LED11 blue, top\n"},
		{LED12, RED,   TOPSIDE, "LED12 red, top\n"},
		{LED12, GREEN, TOPSIDE, "LED12 green, top\n"},
		{LED12, BLUE,  TOPSIDE, "LED12 blue, top\n"},
		{LED13, RED,   TOPSIDE, "LED13 red, top\n"},
		{LED13, GREEN, TOPSIDE, "LED13 green, top\n"},
		{LED13, BLUE,  TOPSIDE, "LED13 blue, top\n"},
		{LED14, RED,   TOPSIDE, "LED14 red, top\n"},
		{LED14, GREEN, TOPSIDE, "LED14 green, top\n"},
		{LED14, BLUE,  TOPSIDE, "LED14 blue, top\n"},
		{LED15, RED,   TOPSIDE, "LED15 red, top\n"},
		{LED15, GREEN, TOPSIDE, "LED15 green, top\n"},
		{LED15, BLUE,  TOPSIDE, "LED15 blue, top\n"},
		{LED16, RED,   TOPSIDE, "LED16 red, top\n"},
		{LED16, GREEN, TOPSIDE, "LED16 green, top\n"},
		{LED16, BLUE,  TOPSIDE, "LED16 blue, top\n"},
		{LED1,  RED,   BOTTOMSIDE, "LED1  red, bottom\n"},
		{LED1,  GREEN, BOTTOMSIDE, "LED1  green, bottom\n"},
		{LED1,  BLUE,  BOTTOMSIDE, "LED1  blue, bottom\n"},
		{LED2,  RED,   BOTTOMSIDE, "LED2  red, bottom\n"},
		{LED2,  GREEN, BOTTOMSIDE, "LED2  green, bottom\n"},
		{LED2,  BLUE,  BOTTOMSIDE, "LED2  blue, bottom\n"},
		{LED3,  RED,   BOTTOMSIDE, "LED3  red, bottom\n"},
		{LED3,  GREEN, BOTTOMSIDE, "LED3  green, bottom\n"},
		{LED3,  BLUE,  BOTTOMSIDE, "LED3  blue, bottom\n"},
		{LED4,  RED,   BOTTOMSIDE, "LED4  red, bottom\n"},
		{LED4,  GREEN, BOTTOMSIDE, "LED4  green, bottom\n"},
		{LED4,  BLUE,  BOTTOMSIDE, "LED4  blue, bottom\n"},
		{LED5,  RED,   BOTTOMSIDE, "LED5  red, bottom\n"},
		{LED5,  GREEN, BOTTOMSIDE, "LED5  green, bottom\n"},
		{LED5,  BLUE,  BOTTOMSIDE, "LED5  blue, bottom\n"},
		{LED6,  RED,   BOTTOMSIDE, "LED6  red, bottom\n"},
		{LED6,  GREEN, BOTTOMSIDE, "LED6  green, bottom\n"},
		{LED6,  BLUE,  BOTTOMSIDE, "LED6  blue, bottom\n"},
		{LED7,  RED,   BOTTOMSIDE, "LED7  red, bottom\n"},
		{LED7,  GREEN, BOTTOMSIDE, "LED7  green, bottom\n"},
		{LED7,  BLUE,  BOTTOMSIDE, "LED7  blue, bottom\n"},
		{LED8,  RED,   BOTTOMSIDE, "LED8  red, bottom\n"},
		{LED8,  GREEN, BOTTOMSIDE, "LED8  green, bottom\n"},
		{LED8,  BLUE,  BOTTOMSIDE, "LED8  blue, bottom\n"},
		{LED9,  RED,   BOTTOMSIDE, "LED9  red, bottom\n"},
		{LED9,  GREEN, BOTTOMSIDE, "LED9  green, bottom\n"},
		{LED9,  BLUE,  BOTTOMSIDE, "LED9  blue, bottom\n"},
		{LED10, RED,   BOTTOMSIDE, "LED10 red, bottom\n"},
		{LED10, GREEN, BOTTOMSIDE, "LED10 green, bottom\n"},
		{LED10, BLUE,  BOTTOMSIDE, "LED10 blue, bottom\n"},
		{LED11, RED,   BOTTOMSIDE, "LED11 red, bottom\n"},
		{LED11, GREEN, BOTTOMSIDE, "LED11 green, bottom\n"},
		{LED11, BLUE,  BOTTOMSIDE, "LED11 blue, bottom\n"},
		{LED12, RED,   BOTTOMSIDE, "LED12 red, bottom\n"},
		{LED12, GREEN, BOTTOMSIDE, "LED12 green, bottom\n"},
		{LED12, BLUE,  BOTTOMSIDE, "LED12 blue, bottom\n"},
		{LED13, RED,   BOTTOMSIDE, "LED13 red, bottom\n"},
		{LED13, GREEN, BOTTOMSIDE, "LED13 green, bottom\n"},
		{LED13, BLUE,  BOTTOMSIDE, "LED13 blue, bottom\n"},
		{LED14, RED,   BOTTOMSIDE, "LED14 red, bottom\n"},
		{LED14, GREEN, BOTTOMSIDE, "LED14 green, bottom\n"},
		{LED14, BLUE,  BOTTOMSIDE, "LED14 blue, bottom\n"},
		{LED15, RED,   BOTTOMSIDE, "LED15 red, bottom\n"},
		{LED15, GREEN, BOTTOMSIDE, "LED15 green, bottom\n"},
		{LED15, BLUE,  BOTTOMSIDE, "LED15 blue, bottom\n"},
		{LED16, RED,   BOTTOMSIDE, "LED16 red, bottom\n"},
		{LED16, GREEN, BOTTOMSIDE, "LED16 green, bottom\n"},
		{LED16, BLUE,  BOTTOMSIDE, "LED16 blue, bottom\n"}
};


/*
 ** ===================================================================
 **  Method      :  test
 */
/**
 *  @brief
 *  	Test all output ports (automatic test mode)
 *  	
 *  Returns only if ESC key is pressed.
 */
/* ===================================================================*/
void test(void){

	operating_mode = TESTING;
	clear_leds(TOPSIDE);
	write_ledColumn(TOPSIDE);
	usb_puts("\nEuler Wheel: Test Hardware (automatic test mode)\n\n");
	usb_puts("Enter any character for next test step, \nESC to go back to CLI (interactive mode)\n\n");

	int stepno = 0;
	int c;
	bool noEvent = TRUE;
	
	ButtonPressed = FALSE;
	ButtonLongPressed = FALSE;
	while(1) {
		noEvent = TRUE;
		while (noEvent) {
			c =  usb_getc(10);
			if (c == A_ESC || ButtonLongPressed) {
				ButtonLongPressed = FALSE;
				clear_leds(TOPSIDE);	
				write_ledColumn(TOPSIDE);
				wait_10ms(2);
				clear_leds(BOTTOMSIDE);	
				write_ledColumn(BOTTOMSIDE);				
				return;
			}
			if (c != ERR_TIMEOUT) {
				noEvent = FALSE;
			} 
			if (ButtonPressed) {
				// debounce time
				wait_10ms(5);
				ButtonPressed = FALSE;
				noEvent = FALSE;
			}
		}
		clear_leds(TOPSIDE);
		clear_leds(BOTTOMSIDE);
		set_led(steps_a[stepno].surface, steps_a[stepno].nr, steps_a[stepno].color);
		write_ledColumn(steps_a[stepno].surface);
		usb_puts(steps_a[stepno].text);
		if (++stepno >= TEST_STEPS)
			stepno = 0;
	}
}

/**
 ** @}
 */

