#if defined(__aarch64__) || defined(_M_ARM64)

#include "context/Lgs_Aarch64.h"
#include "LgsDefinitions.h"

nakedf void Lgs_switchContext() {
    asm(
        "mov x9, sp\n"
        "stp x9, x19, [x0, #0]\n"
        "stp x20, x21, [x0, #16]\n"
        "stp x22, x23, [x0, #32]\n"
        "stp x24, x25, [x0, #48]\n"
        "stp x26, x27, [x0, #64]\n"
        "stp x28, x29, [x0, #80]\n"
        "str x30, [x0, #96]\n"
        "adr x9, 1f\n"
        "str x9, [x0, #104]\n"

        "ldp x9, x19, [x1, #0]\n"
        "mov sp, x9\n"
        "ldp x20, x21, [x1, #16]\n"
        "ldp x22, x23, [x1, #32]\n"
        "ldp x24, x25, [x1, #48]\n"
        "ldp x26, x27, [x1, #64]\n"
        "ldp x28, x29, [x1, #80]\n"
        "ldr x30, [x1, #96]\n"
        "ldr x9, [x1, #104]\n"
        "br x9\n"
        "1:\n"
        "ret\n"
        ::: "memory"
    );
}

void Lgs_reset(Lgs_Aarch64Context* ctx, void* stackTop, void* entryPoint) {
    auto* sp = static_cast<char*>(stackTop);
    sp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(sp) & ~15ULL);
    sp -= 16;

    ctx->sp = sp;
    ctx->x19 = nullptr;
    ctx->x20 = nullptr;
    ctx->x21 = nullptr;
    ctx->x22 = nullptr;
    ctx->x23 = nullptr;
    ctx->x24 = nullptr;
    ctx->x25 = nullptr;
    ctx->x26 = nullptr;
    ctx->x27 = nullptr;
    ctx->x28 = nullptr;
    ctx->x29 = nullptr;
    ctx->x30 = nullptr;
    ctx->pc = entryPoint;
}

#endif
