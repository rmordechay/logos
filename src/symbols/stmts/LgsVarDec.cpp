#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/LgsPtr.h"
#include "utils/LgsUtils.h"

#include <llvm/IR/DIBuilder.h>

Value* LgsVarDec::loadIR(LgsLLVM& codeGen) {
    if (const auto ptr = type->asPtr()) {
        return codeGen.builder.CreateLoad(ptr->baseType->getIRType(codeGen), IRValue);
    }
    return IRValue;
}

bool LgsVarDec::shouldAllocate(const Type* IRType) const {
    if (type->isNumber ||
        type->isVector() ||
        type->asFuncType() ||
        type->asMap() ||
        type->asDArray() ||
        expr->asInstance() ||
        (expr->asFuncCall() && type->isNumber)
    ) return false;
    return !IRType->isArrayTy() && !IRType->isPointerTy() && !IRType->isVoidTy();
}

void LgsVarDec::setDebugValue(LgsLLVM& codeGen) {
    const auto var = codeGen.diBuilder->createAutoVariable(
        codeGen.compileUnit,
        name,
        codeGen.diFile,
        location.lineStart,
        type->getDebugType(codeGen)
    );
    codeGen.diBuilder->insertDeclare(
        IRValue,
        var,
        codeGen.diBuilder->createExpression(),
        getDebugLoc(codeGen),
        codeGen.builder.GetInsertBlock()
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
