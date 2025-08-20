#include "stmts/LgsBreak.h"

#include "logos/LgsCodeGen.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsBreak::createIRValue(LgsCodeGen* codeGen) {
    if (isBreakIf) {
        codeGen->builder.CreateBr(codeGen->stack.outermostIfStmt()->IRExitBlock);
    } else {
        const auto loop = codeGen->stack.currentLoop();
        codeGen->builder.CreateBr(loop->IRExitBlock);
    }
}

json::value LgsBreak::asJSON() {
    assert(0);
}
