#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

void LgsVarDec::createIRStmt(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto IRType = type->getIRType();
    if (expr) {
        const auto exprIRValue = expr->getIRValue(metadata);
        if (IRType->isPointerTy() || IRType->isVoidTy()) {
            IRValue = exprIRValue;
        } else {
            IRValue = builder.CreateAlloca(IRType);
            builder.CreateStore(exprIRValue, IRValue);
        }
    } else {
        IRValue = builder.CreateAlloca(IRType);
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

