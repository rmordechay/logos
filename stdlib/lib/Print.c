#include "Print.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <secure/_string.h>

void print(const char* input, const int values_len, const char* values[]) {
    char output[1024];
    int input_index = 0;
    int output_index = 0;
    int value_index = 0;
    while (input[input_index] != '\0') {
        if (input[input_index] == '%') {
            if (input[input_index + 1] == 'v') {
                if (value_index < values_len) {
                    const char* replacement = values[value_index++];
                    size_t len = strlen(replacement);
                    strncpy(&output[output_index], replacement, len);
                    output_index += len;
                }
                input_index += 2;
                continue;
            }
        }
        output[output_index++] = input[input_index++];
    }
    output[output_index] = '\0';
    fwrite(output, sizeof(char), strlen(output), stdout);
}
