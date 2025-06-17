#include "stmts/LgsBreakStmt.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsBreakStmt::createIRStmt(LgsRuntime* runtime) {
    if (tag != "") {
        for (auto it = runtime->stack.begin(); it != runtime->stack.end(); ++it) {
            const auto outerIfStmt = it->ifStmt;
            if (!outerIfStmt || outerIfStmt->tag != tag) continue;
            runtime->builder.CreateBr(outerIfStmt->endBlock);
            runtime->builder.SetInsertPoint(outerIfStmt->endBlock);
            break;
        }
    } else {
        const auto loop = runtime->stack.getLoop();
        const auto loopExit = loop->IRExitBlock;
        runtime->builder.CreateBr(loopExit);
        breakBlock = createBasicBlock("break", context);
        startBlock(runtime, breakBlock);
        runtime->builder.SetInsertPoint(breakBlock);
    }
}
