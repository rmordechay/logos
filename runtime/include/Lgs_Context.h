#pragma once

#if defined(__x86_64__) || defined(_M_X64)

struct Lgs_X8664Context {
    void* rsp;
    void* rbp;
    void* rbx;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    void* rip;
    __attribute__((naked)) static void switchContext(Lgs_X8664Context& newContext);
    void reset(void* stackTop, void* entryPoint);
};

inline __attribute__((naked)) void Lgs_X8664Context::switchContext(Lgs_X8664Context& newContext) {
    asm volatile(
        "mov %rsp, (%rdi)\n"
        "mov %rbp, 8(%rdi)\n"
        "mov %rbx, 16(%rdi)\n"
        "mov %r12, 24(%rdi)\n"
        "mov %r13, 32(%rdi)\n"
        "mov %r14, 40(%rdi)\n"
        "mov %r15, 48(%rdi)\n"
        "lea 1f(%rip), %rax\n"
        "mov %rax, 56(%rdi)\n"

        "mov (%rsi), %rsp\n"
        "mov 8(%rsi), %rbp\n"
        "mov 16(%rsi), %rbx\n"
        "mov 24(%rsi), %r12\n"
        "mov 32(%rsi), %r13\n"
        "mov 40(%rsi), %r14\n"
        "mov 48(%rsi), %r15\n"
        "jmp *56(%rsi)\n"
        "1:\n"
        "ret\n"
    );
}

inline void Lgs_X8664Context::reset(void* stackTop, void* entryPoint) {
    rsp = static_cast<char*>(stackTop) - 8;
    rbp = nullptr;
    rbx = nullptr;
    r12 = nullptr;
    r13 = nullptr;
    r14 = nullptr;
    r15 = nullptr;
    rip = entryPoint;
}
using Lgs_Context = Lgs_X8664Context;

#elif defined(__aarch64__) || defined(_M_ARM64)

struct Lgs_Aarch64Context {
    void* sp;
    void* x19;
    void* x20;
    void* x21;
    void* x22;
    void* x23;
    void* x24;
    void* x25;
    void* x26;
    void* x27;
    void* x28;
    void* x29;
    void* x30;
    void* pc;
    __attribute__((naked)) static void switchContext(Lgs_Aarch64Context& newContext);
    void reset(void* stackTop, void* entryPoint);
};

__attribute__((naked)) inline void Lgs_Aarch64Context::switchContext(Lgs_Aarch64Context& newContext) {
    asm volatile(
        "mov x9, sp\n"
        "str x9, [x0]\n"
        "str x19, [x0, #8]\n"
        "str x20, [x0, #16]\n"
        "str x21, [x0, #24]\n"
        "str x22, [x0, #32]\n"
        "str x23, [x0, #40]\n"
        "str x24, [x0, #48]\n"
        "str x25, [x0, #56]\n"
        "str x26, [x0, #64]\n"
        "str x27, [x0, #72]\n"
        "str x28, [x0, #80]\n"
        "str x29, [x0, #88]\n"
        "str x30, [x0, #96]\n"
        "adr x9, 1f\n"
        "str x9, [x0, #104]\n"

        "ldr x9, [x1]\n"
        "mov sp, x9\n"
        "ldr x19, [x1, #8]\n"
        "ldr x20, [x1, #16]\n"
        "ldr x21, [x1, #24]\n"
        "ldr x22, [x1, #32]\n"
        "ldr x23, [x1, #40]\n"
        "ldr x24, [x1, #48]\n"
        "ldr x25, [x1, #56]\n"
        "ldr x26, [x1, #64]\n"
        "ldr x27, [x1, #72]\n"
        "ldr x28, [x1, #80]\n"
        "ldr x29, [x1, #88]\n"
        "ldr x30, [x1, #96]\n"
        "ldr x9, [x1, #104]\n"
        "br x9\n"
        "1:\n"
        "ret\n"
        :::
    );
}

inline void Lgs_Aarch64Context::reset(void* stackTop, void* entryPoint) {
    sp = stackTop;
    x19 = nullptr;
    x20 = nullptr;
    x21 = nullptr;
    x22 = nullptr;
    x23 = nullptr;
    x24 = nullptr;
    x25 = nullptr;
    x26 = nullptr;
    x27 = nullptr;
    x28 = nullptr;
    x29 = nullptr;
    x30 = nullptr;
    pc = entryPoint;
}

using Lgs_Context = Lgs_Aarch64Context;
#endif
