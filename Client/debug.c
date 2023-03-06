#include "client.h"

void debug(const char *fmt, ...)
{
    #ifdef DEBUG
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    #else
    (void)fmt;
    #endif
}