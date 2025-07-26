#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsStack::enterScope(const LgsScope scope, LgsValue* value) {
    if (scope == FUNC_SCOPE) {
        push(LgsStackFrame{.scopeType = FUNC_SCOPE, .func = dynamic_cast<LgsFunc*>(value)});
    } else {
        LgsStackFrame stackFrame{.scopeType = scope, .symbolTable = top().symbolTable};
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
        stackFrame.func = currentFunc();
        push(stackFrame);
    }
}

void LgsStack::exitScope() {
    pop();
}

LgsFunc* LgsStack::currentFunc() {
    return top().func;
}

LgsForLoop* LgsStack::currentLoop() {
    return top().loop;
}

auto LgsStack::begin() {
    return c.begin();
}

auto LgsStack::end() {
    return c.end();
}

auto LgsStack::rbegin() {
    return c.rbegin();
}

auto LgsStack::rend() {
    return c.rend();
}

