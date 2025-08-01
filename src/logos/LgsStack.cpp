#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsStack::enterScope(const LgsScope scope, LgsValue* value) {
    LgsStackFrame stackFrame;
    switch (scope) {
    case LOOP_SCOPE:
        stackFrame = {.scopeType = scope, .symbolTable = top().symbolTable};
        stackFrame.loop = dynamic_cast<LgsForLoop*>(value);
        stackFrame.func = currentFunc();
        push(stackFrame);
        return;
    case IF_SCOPE:
        stackFrame = {.scopeType = scope, .symbolTable = top().symbolTable};
        stackFrame.ifStmt = dynamic_cast<LgsIfStmt*>(value);
        stackFrame.func = currentFunc();
        push(stackFrame);
        return;
    case FUNC_SCOPE:
        const auto func = dynamic_cast<LgsFunc*>(value);
        stackFrame = {.scopeType = FUNC_SCOPE, .func = func};
        push(stackFrame);
        return;
    }
}

void LgsStack::exitScope() {
    pop();
}

LgsFunc* LgsStack::currentFunc() {
    return top().func;
}

LgsStmtsBlock* LgsStack::currentStmtsBlock() {
    switch (top().scopeType) {
    case FUNC_SCOPE:
        return currentFunc()->stmtBlock;
    case LOOP_SCOPE:
        return currentLoop()->stmtBlock;
    case IF_SCOPE:
        return currentFunc()->stmtBlock;
    }
    return nullptr;
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