#include <logos/LgsStack.h>
#include "codegen/CodegenMetadata.h"
#include "funcs/LgsFunc.h"

void LgsStack::enterFunc(LgsFunc* func) {
    push(LgsStackFrame{.func = func});
    currentFunc = func;
}

void LgsStack::enterScope() {
    push(LgsStackFrame{
        .symbols = top().symbols,
        .func = top().func,
        .loop = top().loop
    });
}

void LgsStack::exitFunc() {
    pop();
    returnFunc = nullptr;
    currentFunc = nullptr;
}

void LgsStack::exitScope() {
    pop();
}

void LgsStack::addSymbol(const string& name, const LgsSymbol& symbol) {
    assert(size() > 0);
    top().symbols[name] = symbol;
}
