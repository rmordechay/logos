#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsStack::enterScope(LgsValue* value) {
    LgsStackFrame stackFrame;
    if (const auto func = dynamic_cast<LgsFunc*>(value)) {
        stackFrame = {.func = func};
    } else {
        stackFrame = {.func = currentFunc(), .symbolTable = top().symbolTable};
        stackFrame.loop = currentLoop();
        if (const auto forLoop = dynamic_cast<LgsForLoop*>(value)) {
            stackFrame.loop = forLoop;
        }
    }
    push(stackFrame);
}

void LgsStack::exitScope() {
    pop();
}

LgsFunc* LgsStack::currentFunc() {
    return top().func;
}

LgsStmtsBlock* LgsStack::currentStmtsBlock() {
    return top().stmtsBlock;
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