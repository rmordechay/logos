#include "stmts/LgsBreakStmt.h"
#include "funcs/LgsFunc.h"

#include "loops/LgsForLoop.h"
#include "stmts/LgsIfStmt.h"

void LgsBreakStmt::createIRStmt(LgsRuntime* runtime) {
    if (tag != "") {
        for (auto it = runtime->stack.begin(); it != runtime->stack.end(); ++it) {
            const auto outerIfStmt = it->ifStmt;
            if (!outerIfStmt || outerIfStmt->tag != tag) continue;
            runtime->builder.CreateBr(outerIfStmt->IRIfEndBlock);
            runtime->builder.SetInsertPoint(outerIfStmt->IRIfEndBlock);
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
