/**
 *  @brief
 *  	Displays a pattern all around the wheel except there is
 *  	a window (see module display).
 *  	
 *  	The pattern is about 10 % faster than the wheel
 *      
 *  @file
 *      bling.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-28
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef BLING_H_
#define BLING_H_

//extern volatile uint8_t blingLength;
extern volatile bool blingOn[BOTTOMSIDE+1];

/*
 ** ===================================================================
 **  Method      :  bling_Init
 */
/**
 *  @brief
 *  	Initialises the counters
 */
/* ===================================================================*/
void bling_Init();

/*
** ===================================================================
**  Method      :  bling_StartTimer
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (restart counter)
 */
/* ===================================================================*/
void bling_StartTimer();

/*
** ===================================================================
**  Method      :  bling_StopTimer
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (restart counter)
 */
/* ===================================================================*/
void bling_StopTimer();

/*
** ===================================================================
**  Method      :  bling_StartColumn
*/
/**
 *  @brief
 *  	Interrupt from ColumnTimer (restart counter)
 */
/* ===================================================================*/
void bling_StartColumn();


#endif /* BLING_H_ */
