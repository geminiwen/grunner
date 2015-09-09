//
// Created by 温盛章 on 9/1/15.
//

#include "debug.h"
void DEBUG(char *s, ...) {
#ifdef _DEBUG
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    va_end(args);
#endif
}
