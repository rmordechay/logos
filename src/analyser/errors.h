#ifndef LOGOS_ERRORS_H
#define LOGOS_ERRORS_H

#include <stdlib.h>

#define MAX_ERRORS 50
#define MAX_ERROR_MSG_SIZE 2048


#define OBJECT_DOES_NOT_IMPLEMENT_INTERFACE_CODE 1000
#define OBJECT_FIELD_DOES_NOT_IMPLEMENT_INTERFACE_CODE 1001
const char *OBJECT_DOES_NOT_IMPLEMENT_INTERFACE_MSG = "Object '%s' does not implement interface '%s'";
const char *OBJECT_FIELD_DOES_NOT_IMPLEMENT_INTERFACE_MSG = "Field '%s' of object '%s' does not implement interface '%s'";

typedef struct Error {
    int error_code;
    char *message;
    int error_count;
} Error;

void add_error(int error_code, char *message);

#endif //LOGOS_ERRORS_H
