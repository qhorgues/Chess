#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <errno.h>
#include <string.h>

typedef enum Error_type
{
    STATUS = 0,
    WARN = 1,
    ERROR = 2,
    FATAL_ERROR = 3
} Error_type;

void _test(Error_type type_error, int condition, const char* str_condition, const char* message, int line, const char* file);
#define test(type_error, condition, message) _test(type_error, condition, #condition, message, __LINE__, __FILE__)
#define DEFAULT_MESSAGE strerror(errno)


#ifndef NDEBUG
    void open_log(void);
    void logged(Error_type type, const char* format, ...);
    void close_log(void);
    FILE* get_log_file(void);
#else
    #define open_log()
    #define logged(type, str, ...)
    #define close_log()
    #define get_log_file() NULL;
#endif

#endif