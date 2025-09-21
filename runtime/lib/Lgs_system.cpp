#include <stdlib.h>

extern "C" const char* Lgs_System_getEnv(const char* key, const char* defaultKey) {
    const auto env = std::getenv(key);
    if (env) return env;
    return defaultKey;
}

extern "C" void Lgs_System_sleep(const long seconds) {
    std::this_thread::sleep_for(seconds * std::chrono::seconds(1));
}
