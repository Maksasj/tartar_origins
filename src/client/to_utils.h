#ifndef _TO_SERVER_UTILS_H_
#define _TO_SERVER_UTILS_H_

#include <stdio.h>
#include <stdarg.h>

typedef enum TO_LOG_LEVEL {
    TO_INFO,
    TO_WARNING,
    TO_ERROR
} TO_LOG_LEVEL;

char* to_stringify_log_level(TO_LOG_LEVEL logLevel);

void to_log(TO_LOG_LEVEL logLevel, const char *format, ...);

#define TO_LOG(logLevel, ...) to_log(logLevel, __VA_ARGS__)

#endif