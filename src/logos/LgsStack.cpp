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

LgsFunc* LgsStack::getCurrentFunc() {
    return top().func;
}

LgsStmtsBlock* LgsStack::getCurrentStmtsBlock() {
    return top().stmtsBlock;
}

LgsForLoop* LgsStack::getCurrentLoop() {
    for (auto it = rbegin(); it != rend(); ++it) {
        if (it->loop) return it->loop;
    }
    return nullptr;
}
