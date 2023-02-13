#include <stdio.h>
#include <stdlib.h>
#include "log.h"

#define UNUSED(x) (void)(x)
#define BOOL_ALPHA(x) ( (x) ? "true" : "false" )

#ifndef NDEBUG

#include <stdarg.h>

#ifdef WIN32
    #include <fileapi.h>
#else
    #include <sys/stat.h>
#endif

static const char* error_str[] = {"Status", "Warn", "Error", "Fatal Error"};
static bool log_is_open = false;
static FILE* log_file = NULL;

void open_log(void)
{
#ifdef WIN32
    CreateDirectory("./log", NULL);
#else
    mkdir("log", S_IRWXU);
#endif

    log_file = fopen("./log/info.log", "w+");
    if (log_file != NULL)
    {
        log_is_open = true;
    }
}

void logged(Error_type type, const char* format, ...)
{
    if (log_is_open)
    {
        va_list args;
        va_start(args, format);
        fprintf(log_file, "[%s] : ", error_str[type]);
        vfprintf(log_file, format, args);
        va_end(args);
    }
    
}

void close_log(void)
{
    if (log_is_open)
    {
        fclose(log_file);
        log_file = NULL;
        log_is_open = false;
    }
}

FILE* get_log_file(void)
{
    if (log_is_open)
    {
        return log_file;
    }
    return NULL;
}
#endif


void _test(Error_type type_error, int condition, const char* str_condition, const char* message, int line, const char* func, const char* file)
{
#ifndef NDEBUG
    if (log_is_open)
    {
        fprintf(log_file, "[%s] : %s is %s  ---- %s %s:%d in function %s\n", 
                            (!condition) ? error_str[type_error] : "Success", 
                            str_condition, 
                            BOOL_ALPHA(condition), 
                            (!condition) ? message : "", 
                            file, line, func);
    }
#else
    UNUSED(str_condition);
    UNUSED(message);
    UNUSED(line);
    UNUSED(file);
#endif
    if (type_error == FATAL_ERROR && !condition)
    {
        close_log();
        exit(-1);
    }
}
