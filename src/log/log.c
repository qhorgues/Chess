#include <stdio.h>
#include <stdlib.h>
#include "log.h"

#define UNUSED(x) (void)(x)

#ifndef NDEBUG

#include <stdarg.h>
#include <sys/stat.h>

static const char* error_str[] = {"Status", "Warn", "Error", "Fatal Error"};
static bool log_is_open = false;
static FILE* log_file = NULL;

void open_log(void)
{
    mkdir("log", S_IRWXU);
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
    }
}
#endif


void _test(Error_type type_error, int condition, const char* str_condition, const char* message, int line, const char* file)
{
#ifndef NDEBUG
    if (log_is_open)
    {
        fprintf(log_file, "[%s] : %s is %s  ---- %s line : %d, file %s\n", error_str[type_error], str_condition, (condition) ? "true" : "false", message, line, file);
    }
#else
    UNUSED(str_condition);
    UNUSED(message);
    UNUSED(line);
    UNUSED(file);
#endif
    if (type_error == FATAL_ERROR && condition)
    {
        exit(-1);
    }
}
