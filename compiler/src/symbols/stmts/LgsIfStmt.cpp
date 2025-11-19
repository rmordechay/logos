#include "stmts/LgsIfStmt.h"
#include "funcs/LgsFunc.h"
#include "codegen/LgsLLVMGen.h"
#include "LgsUtils.h"

LgsIfStmt::~LgsIfStmt() {
    if (ifCond) {
        delete ifCond;
        ifCond = nullptr;
    }
    if (ifBlock) {
        delete ifBlock;
        ifBlock = nullptr;
    }
    if (elseBlock) {
        delete elseBlock;
        elseBlock = nullptr;
    }
    for (const auto& [expr, block] : elseIfs) {
        freeExpr(expr);
        delete block;
    }
    elseIfs.clear();
}

