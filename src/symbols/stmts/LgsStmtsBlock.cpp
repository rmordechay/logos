#include "stmts/LgsStmtsBlock.h"
#include "LgsDefinitions.h"
#include "exprs/unary/LgsSelection.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsReturn.h"

void LgsStmtsBlock::createIRValue(LgsCodeGen* codeGen) {
    const auto withCleanup = needsCleanup();
    if (withCleanup) {
        initCleanup(codeGen);
    }
    for (const auto stmt : stmts) {
        stmt->createIRStmt(codeGen);
    }
    if (withCleanup) {
        cleanup(codeGen);
    }
}

void LgsStmtsBlock::cleanup(LgsCodeGen* codeGen) {
    codeGen->branchAndStartBlock(cleanupBlock);
    codeGen->builder.CreateRet(returnPhiNode);
}

void LgsStmtsBlock::initCleanup(LgsCodeGen* codeGen) {
    cleanupBlock = codeGen->createBlock(BLOCK_NAME_CLEANUP);
    const auto currentFunc = codeGen->stack.currentFunc();
    const auto IRReturnType = currentFunc->funcType->rt->getIRType(codeGen);
    returnPhiNode = codeGen->builder.CreatePHI(IRReturnType, returnExprs.size());
}

LgsStmt* LgsStmtsBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

bool LgsStmtsBlock::needsCleanup() const {
    if (heapAllocExprs.size() == 1 && returnExprs.size() == 1) {
        return !heapAllocExprs.front()->equals(returnExprs.front());
    }
    return !heapAllocExprs.empty();
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
