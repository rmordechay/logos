#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct Lgs_iterator Lgs_Iterator;
typedef bool (*Lgs_Iterator_hasNext)(Lgs_Iterator* iter);
typedef void* (*Lgs_Iterator_next)(Lgs_Iterator* iter);

struct Lgs_iterator {
    void* container;
    size_t current;
    void* entry;
    Lgs_Iterator_hasNext hasNext;
    Lgs_Iterator_next next;
    void (*reset)(Lgs_iterator* iter);
};

