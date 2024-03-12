#include "to_utils.h"

char* to_stringify_log_level(TO_LOG_LEVEL logLevel) {
    switch (logLevel) {
        case TO_INFO:    { return "INFO"; }
        case TO_WARNING: { return "WARNING"; }
        case TO_ERROR:   { return "ERROR"; }
    }

    return NULL;
}

void to_log(TO_LOG_LEVEL logLevel, const char *format, ...) {
    va_list args;
    va_start(args, format);

    printf("[%s] ", to_stringify_log_level(logLevel));
    vprintf(format, args);
    printf("\n");

    va_end(args);
}