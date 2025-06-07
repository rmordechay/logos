#include <logos/LgsStack.h>

#include "funcs/LgsFunc.h"
#include "stmts/LgsStmt.h"

void LgsStack::enterFunc(LgsFunc* func) {
    push(LgsStackFrame{});
    currentFunc = func;
}

void LgsStack::enterScope(LgsStmt* stmt) {
    assert(currentFunc);
    push(LgsStackFrame{.symbols = top().symbols, .allocatedExprs = top().allocatedExprs});
    if (const auto loop = stmt->asLoop()) {
        currentLoop = loop;
    } else if (const auto ifStmt = stmt->asIfStmt()) {
        currentIfStmt = ifStmt;
    }
}

void LgsStack::exitFunc() {
    pop();
    returnFunc = nullptr;
    currentFunc = nullptr;
    currentLoop = nullptr;
    currentIfStmt = nullptr;
}

void LgsStack::exitScope(const ScopeType type) {
    if (type == IF_STMT) {
        currentIfStmt = nullptr;
    } else if (type == LOOP) {
        currentLoop = nullptr;
    }
    pop();
}

void LgsStack::addSymbol(const string& name, const LgsSymbol& symbol) {
    assert(size() > 0);
    top().symbols[name] = symbol;
}
