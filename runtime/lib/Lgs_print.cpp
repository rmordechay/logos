#include "stmts/LgsField.h"

extern "C" void Lgs_print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
