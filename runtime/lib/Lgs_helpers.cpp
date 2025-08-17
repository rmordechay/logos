#include "Lgs_helpers.h"

#include "configs/LgsDefinitions.h"
#include "configs/LgsErrors.h"

#include <iostream>

size_t Lgs_hash(const char* key) {
    size_t hash = 2166136261u;
    while (*key) {
        hash ^= static_cast<unsigned char>(*key++);
        hash *= FNV_PRIME;
        hash %= MAX_STR_HASH_LEN;
    }
    return hash;
}

void Lgs_printError(const char* key) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s%s not found", LGS_ERROR_STR, key);
    printf("%s\n", buffer);
}

void Lgs_printError2() {
    std::cout << E10067.msg << std::endl;
}
