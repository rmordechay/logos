#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "utils/LgsUtils.h"

bool LgsVarDec::shouldAllocate(const Type* IRType) const {
    if (type->isVector() ||
        type->asFuncType() ||
        type->asMap() ||
        type->asDArray() ||
        expr->asInstance()) return false;
    return !IRType->isArrayTy() && !IRType->isPointerTy() && !IRType->isVoidTy();
}

void LgsVarDec::createIRValue(LgsCodeGen* codeGen) {
    const auto IRType = type->getIRType(codeGen);
    const auto exprIRValue = expr->getIRValue(codeGen);
    if (shouldAllocate(IRType)) {
        IRValue = codeGen->builder.CreateAlloca(IRType, nullptr, name);
        codeGen->builder.CreateStore(exprIRValue, IRValue);
    } else {
        IRValue = exprIRValue;
    }
}

json::object LgsVarDec::asJSON() {
    json::object obj;
    obj["stmtKind"] = "VarDec";
    obj["type"] = type->asJSON();
    obj["expr"] = expr->asJSON();
    return obj;
}

LgsVarDec::~LgsVarDec() {
    if (expr) {
        if (expr->type != type) {
            freeType(type);
            type = nullptr;
        }
        delete expr;
        expr = nullptr;
    } else if (type) {
        freeType(type);
        type = nullptr;
    }
}
