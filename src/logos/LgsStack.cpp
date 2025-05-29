#include "logos/LgsStack.h"
#include "logos/LgsGlobals.h"
#include "funcs/LgsFunc.h"

void LgsStack::enterScope(LgsFunc* func) {
    if (func) {
        returnFunc = currentFunc;
        currentFunc = func;
    }
    if (size() > 0) {
        push(LgsStackFrame{.symbols = top().symbols});
    } else {
        push(LgsStackFrame());
    }
}

void LgsStack::exitScope() {
    pop();
}

void LgsStack::exitFunc() {
    currentFunc = returnFunc;
    returnFunc = nullptr;
    pop();
}

void LgsStack::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    assert(size() > 0);
    top().symbols[name] = symbol;
}

void LgsStack::reset() {
    while (size() > 0) {
        pop();
    }
}

