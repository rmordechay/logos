#include <stdbool.h>
#include <stdlib.h>

typedef void (*Lgs_Defer_invoke)(void* ctx);
typedef void (*Lgs_Defer_destroy)(void* ctx);

typedef struct Lgs_DeferNode {
    Lgs_Defer_invoke invoke;
    Lgs_Defer_destroy destroy;
    void* ctx;
    struct Lgs_DeferNode* next;
} Lgs_DeferNode;

typedef struct {
    Lgs_DeferNode* head;
} Lgs_DeferStack;

static void Lgs_Defer_init(Lgs_DeferStack* s) {
    s->head = NULL;
}

static bool Lgs_Defer_empty(const Lgs_DeferStack* s) {
    return s->head == NULL;
}

void Lgs_Defer_push(Lgs_DeferStack* s, const Lgs_Defer_invoke invoke, const Lgs_Defer_destroy destroy, void* ctx) {
    Lgs_DeferNode* n = malloc(sizeof(Lgs_DeferNode));
    n->invoke = invoke;
    n->destroy = destroy;
    n->ctx = ctx;
    n->next = s->head;
    s->head = n;
}

void Lgs_Defer_run_all(Lgs_DeferStack* s) {
    Lgs_DeferNode* n = s->head;
    s->head = NULL;
    while (n) {
        Lgs_DeferNode* next = n->next;
        n->invoke(n->ctx);
        if (n->destroy) n->destroy(n->ctx);
        free(n);
        n = next;
    }
}
