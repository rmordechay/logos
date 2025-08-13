#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    void** data;
    size_t size;
    size_t capacity;
} Lgs_Stack;

static size_t Lgs_Stack_size(const Lgs_Stack* s) {
    return s->size;
}

static bool Lgs_Stack_empty(const Lgs_Stack* s) {
    return s->size == 0;
}


const char* Lgs_System_getEnv(const char* key, const char* defaultKey) {
    const char* env = getenv(key);
    if (defaultKey) {
        return env ? env : defaultKey;
    }
    return env;
}
