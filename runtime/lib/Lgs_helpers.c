#include "Lgs_helpers.h"

#define FNV_PRIME 16777619
#define MAX_STR_HASH_LEN 1024

size_t Lgs_hash(const char* key) {
    size_t hash = 2166136261u;
    while (*key) {
        hash ^= (unsigned char)*key++;
        hash *= FNV_PRIME;
        hash %= MAX_STR_HASH_LEN;
    }
    return hash;
}
