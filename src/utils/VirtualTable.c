#include "stdio.h"

#define VT_CAPACITY 1000000

typedef struct {
    char* name;
    int position;
} func;

func vtable[VT_CAPACITY] = {0};

int main() {
    // for (int i = 0; i < VT_CAPACITY; i++) {
    //     vtable[i].position = i;
    // }
    for (int i = 0; i < VT_CAPACITY; i++) {
        printf("%s\n", vtable[i].name);
    }
}