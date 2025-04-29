#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "jyggalog.h"

#define BMASK(i,m) (i & m)

// configuration variables
//-----------------------------------------------
static enum jl_level ___jl_log_level = JL_INFO; // Log level
//-----------------------------------------------
static uint8_t ___jl_style = JL_STYLE_DEFAULT;  // output style
//-----------------------------------------------
static void (*___jl_fatal_hook)(void) = NULL;   // fatal hook function
//-----------------------------------------------

//------------------------------------------------------------------------------

void jl_set_level(enum jl_level level){
    ___jl_log_level = level;
}

void jl_set_style(int style){
    ___jl_style = style;
}

void jl_set_fatal_hook(void (*func)(void)){
    ___jl_fatal_hook = func;
}

//------------------------------------------------------------------------------

int jl_jlog(enum jl_level level, const char* file_name, int line_number,FILE* stream, const char* message){
    if(level < ___jl_log_level) return 0;
    // formating: [time-date|level|file:line]: message
    char buf[JL_MAX_MSG_LENGTH] = {0};
    int len = 0;
    
    // start formating
    len += snprintf(buf+len,sizeof(buf) - len, "[");

    time_t t = time(NULL);
    struct tm ltime;
    localtime_s(&ltime,&t);
    if(BMASK(___jl_style, JL_STYLE_TIME) && BMASK(___jl_style,JL_STYLE_DATE)){
        // add time and date
        len += strftime(buf+len,sizeof(buf) - len,"%H:%M:%S-%d/%m/%Y|",&ltime);
    }else if(BMASK(___jl_style, JL_STYLE_TIME)){
        // add time
        len += strftime(buf+len,sizeof(buf) - len,"%H:%M:%S|",&ltime);
    }else if(BMASK(___jl_style, JL_STYLE_DATE)){
        // add date
        len += strftime(buf+len,sizeof(buf) - len,"%d/%m/%Y|",&ltime);
    }

    if(BMASK(___jl_style,JL_STYLE_COLORS)){
        // add colored level
        switch(level){
        case JL_DEBUG:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[36mDEBUG\x1b[0m");
            break;
        case JL_INFO:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[32mINFO\x1b[0m ");
            break;
        case JL_WARN:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[33mWARN\x1b[0m ");
            break;
        case JL_ERROR:  
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[31mERROR\x1b[0m");
            break;
        case JL_FATAL:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[35mFATAL\x1b[0m");
          break;
        default:
            return -1;
            break;
        }
    }else{
        // add level
        switch(level){
        case JL_DEBUG:
            len += snprintf(buf+len, sizeof(buf) - len,"DEBUG");
            break;
        case JL_INFO:
            len += snprintf(buf+len, sizeof(buf) - len,"INFO ");
            break;
        case JL_WARN:
            len += snprintf(buf+len, sizeof(buf) - len,"WARN ");
            break;
        case JL_ERROR:  
            len += snprintf(buf+len, sizeof(buf) - len,"ERROR");
            break;
        case JL_FATAL:
            len += snprintf(buf+len, sizeof(buf) - len,"FATAL");
          break;
        default:
            return -1;
            break;
        }
    }
    

    if (BMASK(___jl_style,JL_STYLE_FILE_NAME) && BMASK(___jl_style, JL_STYLE_LINE_NUMBER)){
        // add file name and line number
        len += snprintf(buf+len,sizeof(buf) - len,"|%s: %d",file_name, line_number);
    }else if (BMASK(___jl_style, JL_STYLE_FILE_NAME)){
        // add file name
        len += snprintf(buf+len,sizeof(buf) - len,"|%s",file_name);
    }else if (BMASK(___jl_style,JL_STYLE_LINE_NUMBER)){
        // add line number
        len += snprintf(buf+len,sizeof(buf) - len,"|%d",line_number);
    }
    
    // add message
    len += snprintf(buf+len,sizeof(buf) - len,"]: %s;\n",message);
    
    // print message
    int r = fprintf(stream,"%s",buf);

    if(level == JL_FATAL){
        if(___jl_fatal_hook) ___jl_fatal_hook();
        exit(EXIT_FAILURE);
    }
    return r;
}
int jl_jlogf(enum jl_level level, const char* file_name, int line_number, FILE* stream, const char* format, ...){
    if(level < ___jl_log_level) return 0;
    // formating: [time-date|level|file:line]: message
    char buf[JL_MAX_MSG_LENGTH] = {0};
    int len = 0;

    va_list va;
    // start formating
    len += snprintf(buf+len,sizeof(buf) - len, "[");
    
    time_t t = time(NULL);
    struct tm ltime;
    localtime_s(&ltime,&t);
    if(BMASK(___jl_style, JL_STYLE_TIME) && BMASK(___jl_style,JL_STYLE_DATE)){
        // add time and date
        len += strftime(buf+len,sizeof(buf) - len,"%H:%M:%S-%d/%m/%Y|",&ltime);
    }else if(BMASK(___jl_style, JL_STYLE_TIME)){
        // add time
        len += strftime(buf+len,sizeof(buf) - len,"%H:%M:%S|",&ltime);
    }else if(BMASK(___jl_style, JL_STYLE_DATE)){
        // add date
        len += strftime(buf+len,sizeof(buf) - len,"%d/%m/%Y|",&ltime);
    }

    if(BMASK(___jl_style,JL_STYLE_COLORS)){
        // add colored level
        switch(level){
        case JL_DEBUG:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[36mDEBUG\x1b[0m");
            break;
        case JL_INFO:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[32mINFO\x1b[0m ");
            break;
        case JL_WARN:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[33mWARN\x1b[0m ");
            break;
        case JL_ERROR:  
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[31mERROR\x1b[0m");
            break;
        case JL_FATAL:
            len += snprintf(buf+len, sizeof(buf) - len,"\x1b[35mFATAL\x1b[0m");
          break;
        default:
            return -1;
            break;
        }
    }else{
        // add level
        switch(level){
        case JL_DEBUG:
            len += snprintf(buf+len, sizeof(buf) - len,"DEBUG");
            break;
        case JL_INFO:
            len += snprintf(buf+len, sizeof(buf) - len,"INFO ");
            break;
        case JL_WARN:
            len += snprintf(buf+len, sizeof(buf) - len,"WARN ");
            break;
        case JL_ERROR:  
            len += snprintf(buf+len, sizeof(buf) - len,"ERROR");
            break;
        case JL_FATAL:
            len += snprintf(buf+len, sizeof(buf) - len,"FATAL");
          break;
        default:
            return -1;
            break;
        }
    }
    
    // format message and add to buf
    if (BMASK(___jl_style,JL_STYLE_FILE_NAME) && BMASK(___jl_style, JL_STYLE_LINE_NUMBER)){
        len += snprintf(buf+len,sizeof(buf) - len,"|%s: %d",file_name, line_number);
    }else if (BMASK(___jl_style, JL_STYLE_FILE_NAME)){
        len += snprintf(buf+len,sizeof(buf) - len,"|%s",file_name);
    }else if (BMASK(___jl_style,JL_STYLE_LINE_NUMBER)){
        len += snprintf(buf+len,sizeof(buf) - len,"|%d",line_number);
    }

    // appends format
    len += snprintf(buf+len,sizeof(buf) - len, "]: ");
    va_start(va,format);
    len += vsnprintf(buf+len,sizeof(buf) - len ,format,va);
    va_end(va);
    len += snprintf(buf + len, sizeof(buf) - len,"\n");

    if(level == JL_FATAL) exit(EXIT_FAILURE);

    // print message
    int r = fprintf(stream,"%s",buf);

    if(level == JL_FATAL){
        if(___jl_fatal_hook) ___jl_fatal_hook();
        exit(EXIT_FAILURE);
    }
    return r;
}
