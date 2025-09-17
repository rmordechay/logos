using Lgs_defer_invoke = void (*)(void* ctx);
using Lgs_defer_destroy = void (*)(void* ctx);

struct Lgs_defer_node {
    Lgs_defer_invoke invoke;
    Lgs_defer_destroy destroy;
    void* ctx;
    Lgs_defer_node* next;
};

struct Lgs_defer_stack {
    Lgs_defer_node* head;
};

inline void Lgs_Defer_init(Lgs_defer_stack* s) {
    s->head = nullptr;
}

inline bool Lgs_Defer_empty(const Lgs_defer_stack* s) {
    return s->head == nullptr;
}

inline void Lgs_Defer_push(Lgs_defer_stack* s, const Lgs_defer_invoke invoke, const Lgs_defer_destroy destroy, void* ctx) {
    auto* n = new Lgs_defer_node;
    n->invoke = invoke;
    n->destroy = destroy;
    n->ctx = ctx;
    n->next = s->head;
    s->head = n;
}

inline void Lgs_Defer_run_all(Lgs_defer_stack* s) {
    auto n = s->head;
    s->head = nullptr;
    while (n) {
        auto next = n->next;
        n->invoke(n->ctx);
        if (n->destroy) n->destroy(n->ctx);
        delete n;
        n = next;
    }
}
