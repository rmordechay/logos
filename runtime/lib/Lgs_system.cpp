#include <iostream>
#include <stdlib.h>

extern "C" const char* System_getEnv(const char* key, const char* defaultKey) {
    const auto env = std::getenv(key);
    if (env) return env;
    return defaultKey;
}
