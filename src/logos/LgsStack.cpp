#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "stmts/LgsStmt.h"

void LgsStack::enterFunc(LgsFunc* func) {
    push(LgsStackFrame{.scopeType = FUNC_SCOPE, .func = func});
    currentFunc = func;
}

void LgsStack::enterScope(const LgsScope scope, LgsStmt* stmt) {
    LgsStackFrame stackFrame{
        .scopeType = scope,
        .symbols = top().symbols,
    };
    switch (scope) {
    case LOOP_SCOPE:
        stackFrame.loop = stmt->asLoop();
        stackFrame.func = currentFunc;
        break;
    case IF_SCOPE:
        stackFrame.ifStmt = stmt->asIfStmt();
        stackFrame.func = currentFunc;
        break;
    case FUNC_SCOPE:
        break;
    }
    push(stackFrame);
}

void LgsStack::exitFunc() {
    pop();
    currentFunc = nullptr;
}

void LgsStack::exitScope(const LgsScope scope) {
    switch (scope) {
    case FUNC_SCOPE:
        break;
    case LOOP_SCOPE:
        break;
    case IF_SCOPE:
        break;
    }
    pop();
}

LgsForLoop* LgsStack::getLoop() {
    return top().loop;
}

LgsIfStmt* LgsStack::getIfStmt() {
    return top().ifStmt;
}

LgsSymbol* LgsStack::getSymbol(const string& name) {
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

void LgsStack::addSymbol(const string& name, const LgsSymbol& symbol) {
    assert(size() > 0);
    top().symbols[name] = symbol;
}
