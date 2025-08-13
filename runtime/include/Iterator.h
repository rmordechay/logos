#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct Iterator Iterator;
typedef bool (*IterHasNext)(Iterator* iter);
typedef void* (*IterNext)(Iterator* iter);

struct Iterator {
    void* container;
    size_t current;
    void* entry;
    IterHasNext hasNext;
    IterNext next;
    void (*reset)(Iterator* iter);
};

static void Iter_reset(Iterator* iter) {
    iter->current = 0;
}
