#include "stmts/LgsStmtsBlock.h"
#include "LgsDefinitions.h"
#include "exprs/unary/LgsSelection.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsReturn.h"

void LgsStmtsBlock::createIRValue(LgsCodeGen* codeGen) {
    for (const auto stmt : stmts) {
        stmt->createIRStmt(codeGen);
    }
    if (needsCleanup()) {
        const auto currentFunc = codeGen->stack.currentFunc();
        codeGen->branchAndStartBlock(getCleanupBlock(codeGen));
        for (const auto expr : heapAllocExprs) {
            expr->type->freeValue(codeGen, expr->getIRValue(codeGen));
        }
        if (hasReturn) {
            codeGen->callPopStack();
            codeGen->builder.CreateRet(currentFunc->returnPhiNode);
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

string LgsStmtsBlock::format(string& indentStr) {
    stringstream oss;
    oss << " {\n";
    indentStr += '\t';
    for (const auto& stmt : stmts) {
        oss << stmt->format(indentStr) << '\n';
    }
    oss << "}\n\n";
    return oss.str();
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
