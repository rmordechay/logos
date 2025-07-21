#ifndef STR_H
#define STR_H
#include <stdbool.h>
#include <stdio.h>

size_t Str_hash(const char* key);
size_t Str_len(const char* str);
bool Str_isEmpty(const char* str);
bool Str_isNotEmpty(const char* str);

#endif //STR_H
