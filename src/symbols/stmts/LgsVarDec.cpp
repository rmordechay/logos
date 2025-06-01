#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "utils/LgsUtils.h"

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

void LgsVarDec::createIRStmt(CodegenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto IRType = type->getIRType();
    const auto exprIRValue = expr->getIRValue(metadata);
    if (IRType->isArrayTy() || IRType->isPointerTy() || IRType->isVoidTy()) {
        IRValue = exprIRValue;
    } else {
        IRValue = builder.CreateAlloca(IRType);
        if (shouldLoadIRArg(exprIRValue)) {
            const auto artIRType = expr->type->getIRType();
            const auto value = metadata->builder.CreateLoad(artIRType, exprIRValue);
            builder.CreateStore(value, IRValue);
        } else {
            builder.CreateStore(exprIRValue, IRValue);
        }
    }
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

