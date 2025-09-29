#include "stmts/LgsIfStmt.h"
#include "funcs/LgsFunc.h"
#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

json::value LgsIfStmt::asJsonStr() {
    json::object obj;
    obj["ifCond"] = ifCond->asJsonStr();
    obj["ifBlock"] = ifBlock->asJsonStr();
    if (elseBlock) obj["elseBlock"] = elseBlock->asJsonStr();
    for (const auto& [expr, block] : elseIfs) {
        json::object elseIfObj;
        elseIfObj["expr"] = expr->asJsonStr();
        elseIfObj["block"] = block->asJsonStr();
        obj["elseIfs"].as_array().emplace_back(elseIfObj);
    }
    return obj;
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

json::value LgsPatternMatching::asJsonStr() {
    assert(0);
}

LgsPatternMatching::~LgsPatternMatching() {
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
