#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef void (*Defer_invoke)(void* ctx);
typedef void (*Defer_destroy)(void* ctx);

typedef struct DeferNode {
    Defer_invoke invoke;
    Defer_destroy destroy;
    void* ctx;
    struct DeferNode* next;
} DeferNode;

typedef struct {
    DeferNode* head;
} DeferStack;

static void Defer_init(DeferStack* s) {
    s->head = NULL;
}

static bool Defer_empty(const DeferStack* s) {
    return s->head == NULL;
}

void Defer_push(DeferStack* s, Defer_invoke invoke, Defer_destroy destroy, void* ctx);
void Defer_run_all(DeferStack* s);
