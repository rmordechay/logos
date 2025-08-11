#include "System.h"
#include <stdlib.h>

const char* System_getEnv(const char* key, const char* defaultKey) {
    const char* env = getenv(key);
    if (defaultKey) {
        return env ? env : defaultKey;
    }
    return env;
}
