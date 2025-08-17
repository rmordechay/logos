using Lgs_Defer_invoke = void (*)(void* ctx);
using Lgs_Defer_destroy = void (*)(void* ctx);

struct Lgs_DeferNode {
    Lgs_Defer_invoke invoke;
    Lgs_Defer_destroy destroy;
    void* ctx;
    Lgs_DeferNode* next;
};

struct Lgs_DeferStack {
    Lgs_DeferNode* head;
};

inline void Lgs_Defer_init(Lgs_DeferStack* s) {
    s->head = nullptr;
}

inline bool Lgs_Defer_empty(const Lgs_DeferStack* s) {
    return s->head == nullptr;
}

inline void Lgs_Defer_push(Lgs_DeferStack* s, const Lgs_Defer_invoke invoke, const Lgs_Defer_destroy destroy, void* ctx) {
    auto* n = new Lgs_DeferNode;
    n->invoke = invoke;
    n->destroy = destroy;
    n->ctx = ctx;
    n->next = s->head;
    s->head = n;
}

inline void Lgs_Defer_run_all(Lgs_DeferStack* s) {
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
