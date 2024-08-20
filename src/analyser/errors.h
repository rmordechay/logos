#ifndef LOGOS_ERRORS_H
#define LOGOS_ERRORS_H

#include <stdlib.h>

#define ERR_FIELDS_NOT_IMPLEMENTED 0, "Fields not implemented"

typedef struct Error {
    int error_code;
    char *message;
} Error;

Error create_error(int error_code, char *message) {
    struct Error err;
    err.error_code = error_code;
    err.message = message;
    return err;
}

#endif //LOGOS_ERRORS_H
