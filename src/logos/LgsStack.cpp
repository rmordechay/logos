#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsStack::enterScope(LgsValue* value, LgsStmtsBlock* stmtsBlock) {
    LgsStackFrame stackFrame = {.stmtsBlock = stmtsBlock};
    if (const auto func = dynamic_cast<LgsFunc*>(value)) {
        stackFrame.func = func;
    } else {
        stackFrame.func = top().func;
        stackFrame.symbolTable = top().symbolTable;
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

LgsSymbolTable& LgsStack::getSymbolTable() {
    return top().symbolTable;
}

void LgsStack::addHeapAllocExpr(LgsExpr* expr) {
    currentStmtsBlock()->heapAllocExprs.push_back(expr);
}

bool LgsStack::isRootScope() const {
    return size() == 1;
}

LgsForLoop* LgsStack::currentLoop() {
    for (auto it = rbegin(); it != rend(); ++it) {
        if (it->loop) return it->loop;
    }
    return nullptr;
}

LgsStmtsBlock* LgsStack::getParentBlock() const {
    assert(this->size() >= 2);
    return this->c[this->size() - 2].stmtsBlock;
}
