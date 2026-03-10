#include <logos/LgsStack.h>
#include <assert.h>
#include <cstddef>

#include "funcs/LgsFunc.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsSwitch.h"

class LgsForeachLoop;

void LgsStack::enterScope(LgsValue* value) {
    LgsStackFrame stackFrame;
    if (const auto func = dynamic_cast<LgsFunc*>(value)) {
        stackFrame.func = func;
    } else if (const auto loop = dynamic_cast<LgsForLoop*>(value)) {
        stackFrame.func = frames.back().func;
        stackFrame.symbolTable = frames.back().symbolTable;
        stackFrame.loop = loop;
    } else if (const auto ifStmt = dynamic_cast<LgsIfStmt*>(value)) {
        stackFrame.func = frames.back().func;
        stackFrame.symbolTable = frames.back().symbolTable;
        stackFrame.ifStmt = ifStmt;
    } else if (const auto ioStmt = dynamic_cast<LgsIOStmt*>(value)) {
        stackFrame.func = frames.back().func;
        stackFrame.symbolTable = frames.back().symbolTable;
        stackFrame.ioStmt = ioStmt;
    } else if (dynamic_cast<LgsSwitch*>(value)) {
        stackFrame.func = frames.back().func;
        stackFrame.symbolTable = frames.back().symbolTable;
    } else {
        assert(0);
    }
    frames.push_back(stackFrame);
}

void LgsStack::exitScope() {
    frames.pop_back();
}

LgsSymbolTable& LgsStack::getSymbolTable() {
    return frames.back().symbolTable;
}

LgsFunc* LgsStack::currentFunc() const {
    return frames.back().func;
}

LgsForLoop* LgsStack::currentLoop() const {
    for (std::size_t i = frames.size(); i-- > 0; ) {
        if (frames[i].loop) return frames[i].loop;
    }
    return nullptr;
}

LgsIfStmt* LgsStack::currentIfStmt() const {
    for (std::size_t i = frames.size(); i-- > 0; ) {
        if (frames[i].ifStmt) return frames[i].ifStmt;
    }
    return nullptr;
}

LgsIfStmt* LgsStack::getOutermostIfStmt() const {
    for (const auto& frame : frames) {
        if (frame.ifStmt) return frame.ifStmt;
    }
    return nullptr;
}

LgsForeachLoop* LgsStack::getInnermostForeachLoop() const {
    for (std::size_t i = frames.size(); i-- > 0; ) {
        const auto& frame = frames[i];
        if (!frame.loop) continue;
        if (const auto forEach = frame.loop->asForeachLoop()) return forEach;
    }
    return nullptr;
}

BasicBlock* LgsStack::findTagExitBlock(const std::string& tag) const {
    for (const auto& frame : frames) {
        if (frame.ifStmt && frame.ifStmt->tag == tag) {
            return frame.ifStmt->IRExitBlock;
        }
    }
    return nullptr;
}
