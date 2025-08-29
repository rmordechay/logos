#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/LgsPtr.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/DIBuilder.h>

Value* LgsVarDec::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);;
}

bool LgsVarDec::shouldAllocate(const Type* IRType) const {
    if (type->asVec() ||
        type->asFuncType() ||
        type->asMap() ||
        type->asDArray() ||
        expr->asInstance() ||
        (expr->asFuncCall() && type->isNumber)
    ) return false;
    return !IRType->isArrayTy() && !IRType->isPointerTy() && !IRType->isVoidTy();
}

void LgsVarDec::setDebugValue(LgsLLVMGen& cg) {
    const auto var = cg.diBuilder->createAutoVariable(
        cg.compileUnit,
        name,
        cg.diFile,
        location.lineStart,
        type->getDebugType(cg)
    );
    cg.diBuilder->insertDeclare(
        IRValue,
        var,
        cg.diBuilder->createExpression(),
        getDebugLoc(cg),
        cg.builder.GetInsertBlock()
    );
}

json::value LgsVarDec::asJSON() {
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
        freeExpr(expr);
        expr = nullptr;
    } else if (type) {
        freeType(type);
        type = nullptr;
    }
}
