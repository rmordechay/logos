#include "Defer.h"
#include <stdlib.h>

void Defer_push(DeferStack* s, const Defer_invoke invoke, const Defer_destroy destroy, void* ctx) {
    DeferNode* n = malloc(sizeof(DeferNode));
    n->invoke = invoke;
    n->destroy = destroy;
    n->ctx = ctx;
    n->next = s->head;
    s->head = n;
}

void Defer_run_all(DeferStack* s) {
    DeferNode* n = s->head;
    s->head = NULL;
    while (n) {
        DeferNode* next = n->next;
        n->invoke(n->ctx);
        if (n->destroy) n->destroy(n->ctx);
        free(n);
        n = next;
    }
}
