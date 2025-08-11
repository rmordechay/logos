#include "Str.h"

#define HASH 2166136261u
#define FNV_PRIME 16777619
#define MAX_STR_LEN 1024

size_t Str_hash(const char* key) {
    size_t h = HASH;
    while (*key) {
        h ^= (unsigned char)*key++;
        h *= FNV_PRIME;
        h %= MAX_STR_LEN;
    }
    return h;
}