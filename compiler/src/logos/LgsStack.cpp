#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsSwitch.h"

void LgsStack::enterScope(LgsValue* value) {
    LgsStackFrame stackFrame;
    if (const auto func = dynamic_cast<LgsFunc*>(value)) {
        stackFrame.func = func;
    } else if (const auto loop = dynamic_cast<LgsForLoop*>(value)) {
        stackFrame.func = stack.top().func;
        stackFrame.symbolTable = stack.top().symbolTable;
        stackFrame.loop = loop;
    } else if (const auto ifStmt = dynamic_cast<LgsIfStmt*>(value)) {
        stackFrame.func = stack.top().func;
        stackFrame.symbolTable = stack.top().symbolTable;
        stackFrame.ifStmt = ifStmt;
    } else if (dynamic_cast<LgsSwitch*>(value)) {
        stackFrame.func = stack.top().func;
        stackFrame.symbolTable = stack.top().symbolTable;
    } else {
        assert(0);
    }
    stack.push(stackFrame);
}

void LgsStack::exitScope() {
    stack.pop();
}

LgsFunc* LgsStack::currentFunc() {
    return stack.top().func;
}

LgsForLoop* LgsStack::currentLoop() {
    return stack.top().loop;
}

LgsIfStmt* LgsStack::currentIfStmt() {
    return stack.top().ifStmt;
}

LgsIfStmt* LgsStack::outermostIfStmt() {
    assert(0);
}

BasicBlock* LgsStack::findTagExitBlock(const std::string& tag) {
    assert(0);
}

LgsSymbolTable& LgsStack::getSymbolTable() {
    return stack.top().symbolTable;
}