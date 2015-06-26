/**
 *  @brief
 *  	A Li-Polymer Charge Management Controller MCP73832T-2ACI/OT is used to 
 *  	charge the battery.
 *  	
 *  	Voltage divider 10 k / 2.2 k
 *  	Vref = 1.195 V
 *  	VAdisable	Input/Output Pin, Input: no voltage divider; Output 0: voltage divider enable
 *  	ChargeStat	Input Pin 0: charging
 *  	ChargeInh	Input/Output Pin, Input: charge enable; Output 1: charge disable
 *  	
 *  	3.0 V minimum battery voltage
 *  	3.7 V nominal battery voltage
  *  	4.2 V maximum charge voltage
 *      
 *  @file
 *      charger.c
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-10-11
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef CHARGER_H_
#define CHARGER_H_

volatile double batteryVoltage;

/*
 ** ===================================================================
 **  Method      :  init_Charger
 */
/**
 *  @brief
 *      Inits the battery measurement
 *  
 */
/* ===================================================================*/
void init_Charger();

/*
 ** ===================================================================
 **  Method      :  enable_BatMeasure
 */
/**
 *  @brief
 *      Enables the battery measurement  
 */
/* ===================================================================*/
void enable_BatMeasure();

/*
 ** ===================================================================
 **  Method      :  disable_BatMeasure
 */
/**
 *  @brief
 *      Disables the battery measurement (e.g. for power down mode)  
 */
/* ===================================================================*/
void disable_BatMeasure();

/*
 ** ===================================================================
 **  Method      :  start_BatMeasure
 */
/**
 *  @brief
 *      Starts the battery measurement
 *  
 *  It is called regularly from a timer interrupt (every 500 us).
 *  After the ADC conversion get_BatMeasure will be called by interrupt. 
 *  
 */
/* ===================================================================*/
void start_BatMeasure();

/*
 ** ===================================================================
 **  Method      :  get_BatMeasure
 */
/**
 *  @brief
 *      Gets the value from the ADC and calculates the voltage
 *  
 *  It is called by the ADC interrupt
 *  
 */
/* ===================================================================*/
void get_BatMeasure();

/*
 ** ===================================================================
 **  Method      :  charger_show_state
 */
/**
 *  @brief
 *      Shows the battery state  
 */
/* ===================================================================*/
void charger_show_state();

#endif /* CHARGER_H_ */
