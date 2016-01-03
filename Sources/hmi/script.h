/**
 *  @brief
 *      Very simple script interpreter. Every line will be interpreted by
 *      CLI except lines beginning with : (colon) or ; (semicolon). After
 *      reading a semicolon the script restarts from the beginning.
 *      A line has to <= 80 chars long.
 *
 *      The script buffer is 800 bytes and shares the same memory for the
 *      images (dotmatrix). That means one buffer has room for about 50
 *      command lines. If that is not enough then you can start another
 *      script buffer within the script.
 *
 *      image_bufferP (see module display) is also as RAM buffer used.
 *
 *      :wait n
 *      waits n seconds
 *
 *		:exit
 *		aborts script
 *
 *      > set script 40
 *      set string upper Hallo
 *      set string lower Velo
 *      set upper string
 *      set lower string
 *      :wait 10
 *      set upper speed
 *      set lower trip
 *      :wait 10
 *      ;
 *
 *		> show script 40
 *
 *      > script start 40
 *      > script stop
 *
 *      > script test 40
 *
 *  @file
 *      script.h
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2016-01-02
 *  @remark
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 *  @version
 *      Version 3.7, 2015/08/11
 */

#ifndef SCRIPT_H_
#define SCRIPT_H_

extern int currScript;
extern bool scriptExecution;
extern bool script_set;

/*
 ** ===================================================================
 **  Method      :  script_Interpreter
 */
/**
 *  @brief
 *      Very simple script interpreter. Every line will be interpreted by
 *      CLI except lines beginning with : (colon) or ; (semicolon). After
 *      reading a semicolon the script restarts from the beginning.
 *
 *      The script buffer is 800 bytes and shares the same memory for the
 *      images (dotmatrix). That means one buffer has room for about 50
 *      command lines.
 *      If that is not enough then you can start another script buffer.
 *
 *  	Called every second by watch_Synch (not called as long as USB is
 *  	active)
 *
 */
/* ===================================================================*/
void script_Interpreter(void);

/*
 ** ===================================================================
 **  Method      :  script_Start
 */
/**
 *  @brief
 *  	Starts the script execution.
 *
 *  @param
 *  	number	image number in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Start(char* number, channelT ch);

/*
 ** ===================================================================
 **  Method      :  script_Stop
 */
/**
 *  @brief
 *  	Stops the script execution.
 *
 *  @param
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Stop(channelT ch);

/*
 ** ===================================================================
 **  Method      :  script_Test
 */
/**
 *  @brief
 *  	Very similar to script_Interpreter but ignores :wait and aborts
 *  	after ;. It shows the commands and their responses.
 *
 *  @param
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Test(char* number, channelT ch);

/*
 ** ===================================================================
 **  Method      :  script_Set
 */
/**
 *  @brief
 *  	set the contents of a script
 *
 *  @param
 *  	number	image number in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Set(char* number, channelT ch);

/*
 ** ===================================================================
 **  Method      :  script_Line
 */
/**
 *  @brief
 *  	saves one script line
 *
 *  @param
 *  	line	script line in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Line(char* line, channelT ch);


/*
 ** ===================================================================
 **  Method      :  script_Show
 */
/**
 *  @brief
 *  	shows the contents of a script
 *
 *  @param
 *  	number	script line in ascii
 *  	ch		channel for the output
 *
 */
/* ===================================================================*/
void script_Show(char* number, channelT ch);

#endif /* SCRIPT_H_ */
