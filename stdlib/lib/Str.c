#include "Str.h"
#include <stdio.h>
#include <string.h>

void replace_substring_inplace(char *src, char* replacements[], const size_t replacements_len) {
    size_t index = 0;
    const char* read = src;
    char* write = src;
    while (*read) {
        if (read[0] == '%' && read[1] == 'v' && index < replacements_len) {
            const char* repl = replacements[index++];
            size_t len = strlen(repl);
            memcpy(write, repl, len);
            write += len;
            read += 2;
        } else {
            *write++ = *read++;
        }
    }
    *write = '\0';
}
