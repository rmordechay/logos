#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsStack::enterScope(LgsValue* value, LgsStmtsBlock* stmtsBlock) {
    LgsStackFrame stackFrame = {.stmtsBlock = stmtsBlock};
    if (const auto func = dynamic_cast<LgsFunc*>(value)) {
        stackFrame.func = func;
    } else if (const auto loop = dynamic_cast<LgsForLoop*>(value)) {
        stackFrame.func = top().func;
        stackFrame.symbolTable = top().symbolTable;
        stackFrame.loop = loop;
    } else if (const auto ifStmt = dynamic_cast<LgsIfStmt*>(value)) {
        stackFrame.func = top().func;
        stackFrame.symbolTable = top().symbolTable;
        stackFrame.ifStmt = ifStmt;
    }
    push(stackFrame);
}

void LgsStack::exitScope() {
    pop();
}

LgsFunc* LgsStack::currentFunc() {
    return top().func;
}

LgsForLoop* LgsStack::currentLoop() {
    for (auto it = rbegin(); it != rend(); ++it) {
        if (it->loop) return it->loop;
    }
    return nullptr;
}

LgsIfStmt* LgsStack::currentIfStmt() {
    for (auto it = rbegin(); it != rend(); ++it) {
        if (it->ifStmt) return it->ifStmt;
    }
    return nullptr;
}

LgsIfStmt* LgsStack::outermostIfStmt() {
    for (auto it = begin(); it != end(); ++it) {
        if (it->ifStmt) return it->ifStmt;
    }
    return nullptr;
}

LgsStmtsBlock* LgsStack::currentStmtsBlock() {
    return top().stmtsBlock;
}

LgsSymbolTable& LgsStack::getSymbolTable() {
    return top().symbolTable;
}

void LgsStack::addHeapAllocExpr(LgsExpr* expr) {
    currentFunc()->heapAllocExprs.push_back(expr);
}

bool LgsStack::isRootScope() const {
    return size() == 1;
}
