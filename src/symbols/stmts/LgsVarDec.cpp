#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "logos/LgsRuntime.h"
#include "utils/LgsUtils.h"

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

void LgsVarDec::createIRStmt(LgsRuntime* runtime) {
    const auto IRType = type->getIRType();
    const auto exprIRValue = expr->getIRValue(runtime);
    if (shouldAllocate(IRType)) {
        IRValue = runtime->builder.CreateAlloca(IRType);
        if (shouldLoadIRArg(exprIRValue)) {
            const auto artIRType = expr->type->getIRType();
            const auto value = runtime->builder.CreateLoad(artIRType, exprIRValue);
            runtime->builder.CreateStore(value, IRValue);
        } else {
            runtime->builder.CreateStore(exprIRValue, IRValue);
        }
    } else {
        IRValue = exprIRValue;
    }
}

bool LgsVarDec::shouldAllocate(const Type* IRType) const {
    return !expr->asInstance() || IRType->isArrayTy() || IRType->isPointerTy() || IRType->isVoidTy();
}

json LgsVarDec::asJSON() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->prettyName();
    tree["stmtType"] = "VAR_DEC";
    return tree;
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}

