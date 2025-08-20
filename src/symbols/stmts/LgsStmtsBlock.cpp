#include "stmts/LgsStmtsBlock.h"
#include "configs/LgsDefinitions.h"
#include "exprs/unary/LgsSelection.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsReturn.h"

void LgsStmtsBlock::createIRValue(LgsCodeGen* codeGen) {
    for (const auto stmt : stmts) {
        stmt->createIRValue(codeGen);
    }
    if (needsCleanup()) {
        cleanupExprs(codeGen);
    }
}

void LgsStmtsBlock::cleanupExprs(LgsCodeGen* codeGen) {
    codeGen->branchAndStartBlock(getCleanupBlock(codeGen));
    const auto currentFunc = codeGen->stack.currentFunc();
    if (returnExpr && codeGen->stack.isRootScope()) {
        const auto IRReturnType = currentFunc->funcType->rt->getIRType(codeGen);
        const auto returnPhiNode = codeGen->builder.CreatePHI(IRReturnType, currentFunc->returnStmts.size());
        for (const auto returnStmt : currentFunc->returnStmts) {
            returnPhiNode->addIncoming(returnStmt->expr->getIRValue(codeGen), returnStmt->parentBlock);
        }
        for (const auto expr : heapAllocExprs) {
            expr->type->freeValue(codeGen, expr->getIRValue(codeGen));
        }
        codeGen->builder.CreateRet(returnPhiNode);
    } else {
        for (const auto expr : heapAllocExprs) {
            expr->type->freeValue(codeGen, expr->getIRValue(codeGen));
        }
        if (returnExpr) {
            const auto stmtsBlock = codeGen->stack.getParentBlock();
            codeGen->builder.CreateBr(stmtsBlock->getCleanupBlock(codeGen));
        }
    }
}

bool LgsStmtsBlock::needsCleanup() const {
    return !heapAllocExprs.empty();
}

BasicBlock* LgsStmtsBlock::getCleanupBlock(LgsCodeGen* codeGen) {
    if (cleanupBlock) return cleanupBlock;
    cleanupBlock = codeGen->createBlock(BLOCK_NAME_CLEANUP);
    return cleanupBlock;
}

LgsStmt* LgsStmtsBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

json::value LgsStmtsBlock::asJSON() {
    json::array jsonStmts;
    for (const auto& stmt : stmts) {
        jsonStmts.emplace_back(stmt->asJSON());
    }
    return jsonStmts;
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
    stmts.clear();
}
