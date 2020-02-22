/*
 * log.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Dan Walkes
 *      Editor: Chutao Wei
 *
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_
#include <stdio.h>
#include <stdint.h>
#define PC_RUN 1
#define INCLUDE_LOGGING 1 
#define INCLUDE_LOG_DEBUG 1
/**
 * Instructions for using this module:
 * 1) #include "log.h" in the C file where you'd like to add logging
 * 2) Reference macros LOG_XXX to log at specific thresholds.  Use printf style argument
 *    lists with each macro to support printing variables.
 *    * ERROR for unexpected conditions which should never occur.
 *    * WARN for potential issues which may occur
 *    * INFO for infrequent status updates
 *    * DEBUG for detailed updates, useful when troubleshooting a specific
 *        code path
 *  Logging can be viewed with Tera Term or similar terminal emulator.
 *       Select baud rate 115200.
 *  All logging is off by default (compiled out of the build)
 *   * To turn on you should #define INCLUDE_LOGGING 1 in your project files or setup a build configuration for
 *       this purpose.
 *  Even after turning logging on with INCLUDE_LOGGING, debug logging is off by default.
 *   * To turn debug logging on for a specific .c file, #define INCLUDE_LOG_DEBUG 1 at the top of the file
 *       before the #include "log.h" reference.
 *   * To turn on for all files #define INCLUDE_LOG_DEBUG 1 in the project configuration.
 */

#ifndef LOG_ERROR
#define LOG_ERROR(message,...) \
	LOG_DO(message,"Error", ##__VA_ARGS__)
#endif

#ifndef LOG_WARN
#define LOG_WARN(message,...) \
	LOG_DO(message,"Warn ", ##__VA_ARGS__)
#endif

#ifndef LOG_INFO
#define LOG_INFO(message,...) \
	LOG_DO(message,"Info ", ##__VA_ARGS__)
#endif

#if INCLUDE_LOG_DEBUG
#ifndef LOG_DEBUG
#define LOG_DEBUG(message,...) \
	LOG_DO(message,"Debug",##__VA_ARGS__)
#define LOG_DEBUG_CODE(code) code
#endif
#else
#define LOG_DEBUG(message,...)
#define LOG_DEBUG_CODE(code)
#endif


#if PC_RUN
#define PC 1
#else
#define PC 0
#endif

#if INCLUDE_LOGGING
#define LOG_DO(message,level, ...) \
	printf( ":%s:%s: " message "\n", level, __func__, ##__VA_ARGS__ )
#else
/**
 * Remove all logging related code on builds where logging is not enabled
 */
#define LOG_DO(message,level, ...)
static inline void logFlush() {}
#endif


#endif /* SRC_LOG_H_ */
