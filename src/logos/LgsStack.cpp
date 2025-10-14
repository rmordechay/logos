#include <logos/LgsStack.h>
#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsPatternMatch.h"

void LgsStack::enterScope(LgsValue* value) {
    LgsStackFrame stackFrame;
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
    } else if (dynamic_cast<LgsPatternMatch*>(value)) {
        stackFrame.func = top().func;
        stackFrame.symbolTable = top().symbolTable;
    } else {
        assert(0);
    }
    if (size() > 0) {
        stackFrame.inCoroutine = top().inCoroutine;
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

BasicBlock* LgsStack::findTagExitBlock(const std::string& tag) {
    for (auto it = begin(); it != end(); ++it) {
        if (it->ifStmt && it->ifStmt->tag == tag) {
            return it->ifStmt->IRExitBlock;
        }
    }
    assert(0);
}

LgsSymbolTable& LgsStack::getSymbolTable() {
    return top().symbolTable;
}

bool LgsStack::inCoroutine() {
    return top().inCoroutine;
}