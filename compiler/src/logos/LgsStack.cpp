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
        stackFrame.func = stack.back().func;
        stackFrame.symbolTable = stack.back().symbolTable;
        stackFrame.loop = loop;
    } else if (const auto ifStmt = dynamic_cast<LgsIfStmt*>(value)) {
        stackFrame.func = stack.back().func;
        stackFrame.symbolTable = stack.back().symbolTable;
        stackFrame.ifStmt = ifStmt;
    } else if (dynamic_cast<LgsSwitch*>(value)) {
        stackFrame.func = stack.back().func;
        stackFrame.symbolTable = stack.back().symbolTable;
    } else {
        assert(0);
    }
    stack.push_back(stackFrame);
}

void LgsStack::exitScope() {
    stack.pop_back();
}

LgsSymbolTable& LgsStack::getSymbolTable() {
    return stack.back().symbolTable;
}

LgsFunc* LgsStack::currentFunc() const {
    return stack.back().func;
}

LgsForLoop* LgsStack::currentLoop() const {
    for (std::size_t i = stack.size(); i-- > 0; ) {
        if (stack[i].loop) return stack[i].loop;
    }
    return nullptr;
}

LgsIfStmt* LgsStack::currentIfStmt() const {
    for (std::size_t i = stack.size(); i-- > 0; ) {
        if (stack[i].ifStmt) return stack[i].ifStmt;
    }
    return nullptr;
}

LgsIfStmt* LgsStack::getOutermostIfStmt() const {
    for (const auto& frame : stack) {
        if (frame.ifStmt) return frame.ifStmt;
    }
    return nullptr;
}

LgsForeachLoop* LgsStack::getInnermostForeachLoop() const {
    for (std::size_t i = stack.size(); i-- > 0; ) {
        const auto& frame = stack[i];
        if (!frame.loop) continue;
        if (const auto forEach = frame.loop->asForeachLoop()) return forEach;
    }
    return nullptr;
}

BasicBlock* LgsStack::findTagExitBlock(const std::string& tag) const {
    for (const auto& frame : stack) {
        if (frame.ifStmt && frame.ifStmt->tag == tag) {
            return frame.ifStmt->IRExitBlock;
        }
    }
    return nullptr;
}
