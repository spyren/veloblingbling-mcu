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
 *  @copyright
 *      Peter Schmid, Switzerland
 *  @author
 *      Peter Schmid, peter@spyr.ch
 *  @date
 *      2014-02-10
 *  @remark     
 *      Language: C, ProcessorExpert, GNU ARM Crosscompiler gcc-v4.2.0
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

extern double logIntervall; 		/**< data log intervall [s] */

#endif /* DATALOGGER_H_ */
