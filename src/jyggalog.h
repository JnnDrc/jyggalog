#ifndef _JYGGALOG_H
#define _JYGGALOG_H

/*
 *
 * A simple logging library, logical and ordered.
 *
 * */

#include <stdio.h>

// The maximum size of a formatted output
#define JL_MAX_MSG_LENGTH 512

// Function like macros --------------------------------------------------------

// macros of the general functions on the end of file, to facilitate your life!

// logging with stream option
#define jl_flog(level, stream, message) jl_jlog(level, __FILE__,__LINE__,stream,message)
#define jl_flogf(level, stream, format, ...) jl_jlogf(level,__FILE__,__LINE__,stream,format,__VA_ARGS__)

// logging to stdout
#define jl_log(level, message) jl_jlog(level, __FILE__,__LINE__,stdout,message)
#define jl_logf(level, format, ...) jl_jlogf(level,__FILE__,__LINE__,stdout,format,__VA_ARGS__)

// loggnig functions to stdout for each level
// debug
#define jl_log_debug(message) jl_jlog(JL_DEBUG, __FILE__,__LINE__,stdout,message)
#define jl_logf_debug(format, ...) jl_jlogf(JL_DEBUG,__FILE__,__LINE__,stdout,format,__VA_ARGS__)
// info
#define jl_log_info(message) jl_jlog(JL_INFO, __FILE__,__LINE__,stdout,message)
#define jl_logf_info(format, ...) jl_jlogf(JL_INFO,__FILE__,__LINE__,stdout,format,__VA_ARGS__)
// warn
#define jl_log_warn(message) jl_jlog(JL_WARN, __FILE__,__LINE__,stdout,message)
#define jl_logf_warn(format, ...) jl_jlogf(JL_WARN,__FILE__,__LINE__,stdout,format,__VA_ARGS__)
// error
#define jl_log_error(message) jl_jlog(JL_ERROR, __FILE__,__LINE__,stdout,message)
#define jl_logf_error(format, ...) jl_jlogf(JL_ERROR,__FILE__,__LINE__,stdout,format,__VA_ARGS__)
// fatal
#define jl_log_fatal(message) jl_jlog(JL_FATAL, __FILE__,__LINE__,stdout,message)
#define jl_logf_fatal(format, ...) jl_jlogf(JL_FATAL,__FILE__,__LINE__,stdout,format,__VA_ARGS__)

// Structs ---------------------------------------------------------------------

// logging level
enum jl_level {
    JL_ALL = 0, // Log all messages                     // used only for jl_set_level
    JL_DEBUG,   // Log debug messages
    JL_INFO,    // Log program execution informations   // Default
    JL_WARN,    // Log recoverable failures
    JL_ERROR,   // Log unrecoverable failures
    JL_FATAL,   // Log fatal messages, abort the program
    JL_NONE     // Log nothing                          // used only for jl_set_level
};

// output style bits
enum jl_output_style {
    JL_STYLE_DEFAULT = 0,       // default logging format, simple and direct
    JL_STYLE_LINE_NUMBER = 1,   // prints line number of the log call
    JL_STYLE_FILE_NAME = 2,     // prints file name of the log call
    JL_STYLE_TIME = 4,          // prints time when log call is made
    JL_STYLE_DATE = 8,          // prints date when log call i made

    JL_STYLE_COLORS = 16        // adds colors to highlight log level
};

// Config functions ------------------------------------------------------------

// set the logging level
// @param level enum jl_level, level
void jl_set_level(enum jl_level level);
// set output formatting style bits
// @param stle int, style options (bit mask, OP1 | OP2 | OP3 ...)
void jl_set_style(int style);
// set the fatal hook function. The fatal hook function is a
// function that is called before the exiting of a fatal log
// @param func (*void)(void), function pointer to hook function
void jl_set_fatal_hook(void (*func)(void));

// Logging functions -----------------------------------------------------------

// general logger
// @param level enum jl_level, logging level of the message
// @param file_name const char*, file caller name, usually __FILE__
// @param line_number int, caller line number, usually __LINE__
// @param stream FILE*, stream to be outputted
// @param message const char*, message
int jl_jlog(enum jl_level level, const char* file_name, int line_number, FILE* stream, const char* message);
// general formatted logger
// @param level enum jl_level, logging level of the message
// @param file_name const char*, file caller name, usually __FILE__
// @param line_number int, caller line number, usually __LINE__
// @param stream FILE*, stream to be outputted
// @param message const char*, format
// @params ..., va args
int jl_jlogf(enum jl_level level, const char* file_name, int line_number, FILE* stream, const char* format, ...);


#endif /* _JYGGALOG_H */
