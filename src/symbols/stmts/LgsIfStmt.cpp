#include "stmts/LgsIfStmt.h"
#include "funcs/LgsFunc.h"
#include "codegen/LgsCodeGen.h"
#include "utils/LgsUtils.h"

json::value LgsIfStmt::asJSON() {
    json::object obj;
    obj["ifCond"] = ifCond->asJSON();
    obj["ifBlock"] = ifBlock->asJSON();
    if (elseBlock) obj["elseBlock"] = elseBlock->asJSON();
    for (const auto& [expr, block] : elseIfs) {
        json::object elseIfObj;
        elseIfObj["expr"] = expr->asJSON();
        elseIfObj["block"] = block->asJSON();
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