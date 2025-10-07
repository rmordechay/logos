#include "stmts/LgsIfStmt.h"
#include "funcs/LgsFunc.h"
#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

void LgsIfStmt::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "kind", "IfStmt", true);
    openJsonKey(json, "ifCond");
    ifCond->parseAsJSON(json);
    closeJsonObject(json);
}

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

LgsPatternMatch::~LgsPatternMatch() {
    if (cond) {
        freeExpr(cond);
        cond = nullptr;
    }
    if (elseBlock) {
        delete elseBlock;
        elseBlock = nullptr;
    }
    for (const auto& [expr, block] : patterns) {
        freeExpr(expr);
        delete block;
    }
    patterns.clear();
}
