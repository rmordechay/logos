#ifndef LOGOS_ERRORS_H
#define LOGOS_ERRORS_H

#include <stdlib.h>

#define MAX_ERRORS 50
#define OBJECT_DOES_NOT_IMPLEMENT_INTERFACE 0, "Object does not implement interface %s"

typedef struct Error {
    int error_code;
    char *message;
} Error;

#endif //LOGOS_ERRORS_H
