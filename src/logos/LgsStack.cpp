#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsStack::enterScope(LgsValue* value, LgsStmtsBlock* stmtsBlock) {
    LgsStackFrame stackFrame = {.stmtsBlock = stmtsBlock};
    if (const auto func = dynamic_cast<LgsFunc*>(value)) {
        stackFrame = {.func = func};
    } else if (const auto ifStmt = dynamic_cast<LgsIfStmt*>(value)) {
        stackFrame = {.func = currentFunc(), .symbolTable = top().symbolTable};
        stackFrame.ifStmt = ifStmt;
        stackFrame.loop = currentLoop();
    } else if (const auto forLoop = dynamic_cast<LgsForLoop*>(value)) {
        stackFrame = {.func = currentFunc(), .symbolTable = top().symbolTable};
        stackFrame.loop = forLoop;
        stackFrame.ifStmt = currentIfStmt();
    } else {
        assert(0);
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

LgsIfStmt* LgsStack::currentIfStmt() {
    return top().ifStmt;
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