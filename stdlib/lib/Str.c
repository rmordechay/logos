#include "Str.h"
#include <string.h>

#define HASH 2166136261u
#define FNV_PRIME 16777619
#define MAX_STR_LEN 1024

size_t Str_hash(const char* key) {
    size_t h = HASH;
    while (*key) {
        h ^= (unsigned char)*key++;
        h *= FNV_PRIME;
    }
    return h;
}

size_t Str_len(const char* str) {
    return strlen(str);
}

bool Str_isEmpty(const char* str) {
    return strlen(str) == 0;
}

bool Str_isNotEmpty(const char* str) {
    return strlen(str) != 0;
}
