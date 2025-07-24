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
        .symbolTable = top().symbolTable,
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
    case BLOCK_SCOPE:
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

void LgsStack::exitScope() {
    pop();
}

LgsForLoop* LgsStack::getLoop() {
    return top().loop;
}

LgsIfStmt* LgsStack::getIfStmt() {
    return top().ifStmt;
}
