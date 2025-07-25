#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsStack::enterScope(const LgsScope scope, LgsValue* value) {
    if (scope == FUNC_SCOPE) {
        const auto func = dynamic_cast<LgsFunc*>(value);
        push(LgsStackFrame{.scopeType = FUNC_SCOPE, .func = func});
        currentFunc = func;
        return;
    }
    LgsStackFrame stackFrame{
        .scopeType = scope,
        .symbolTable = top().symbolTable,
    };
    switch (scope) {
    case LOOP_SCOPE:
        stackFrame.loop = dynamic_cast<LgsForLoop*>(value);
        break;
    case IF_SCOPE:
        stackFrame.ifStmt = dynamic_cast<LgsIfStmt*>(value);
        break;
    case BLOCK_SCOPE:
        stackFrame.stmtsBlock = dynamic_cast<LgsStmtsBlock*>(value);
        break;
    default:
        assert(0);
    }
    stackFrame.func = currentFunc;
    push(stackFrame);
}

void LgsStack::exitScope(const bool isFunc) {
    pop();
    if (isFunc) {
        currentFunc = nullptr;
    }
}

LgsForLoop* LgsStack::getLoop() {
    return top().loop;
}

void LgsStack::addAllocatedExpr(LgsExpr* expr) {
    allocatedExprs.push_back(expr);
}
