#include "logos/LgsRuntime.h"
#include "logos/LgsGlobals.h"
#include "funcs/LgsFunc.h"

void LgsRuntime::enterScope(LgsFunc* func) {
    LgsFunc* currentFunc = nullptr;
    if (func) {
        currentFunc = func;
    } else {
        currentFunc = getCurrentFunc();
    }
    if (stage == LGS_RUNTIME) {
        std::cout << currentFunc->location.getFullPath(currentFunc->path) << std::endl;
    }
    if (stack.empty()) {
        stack.push(LgsStackFrame{.currentFunc = currentFunc});
    } else {
        stack.push(LgsStackFrame{.symbols = stack.top().symbols, .currentFunc = currentFunc, .currentLoop = getCurrentLoop()});
    }
}

void LgsRuntime::exitScope() {
    stack.pop();
}

void LgsRuntime::exitFunc() {
    stack.pop();
}

void LgsRuntime::reset() {
    while (stack.size() > 0) {
        stack.pop();
    }
}

LgsFunc* LgsRuntime::getCurrentFunc() {
    assert(stack.size() > 0);
    return stack.top().currentFunc;
}

LgsForLoop* LgsRuntime::getCurrentLoop() {
    assert(stack.size() > 0);
    return stack.top().currentLoop;
}

void LgsRuntime::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    assert(stack.size() > 0);
    stack.top().symbols[name] = symbol;
}
