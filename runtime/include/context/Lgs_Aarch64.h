#pragma once

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

};

void switchContext(Lgs_Aarch64Context* from, Lgs_Aarch64Context* to);
void reset(Lgs_Aarch64Context* ctx, void* stackTop, void* entryPoint);
using Lgs_Context = Lgs_Aarch64Context;