#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

void LgsVarDec::createIRStmt(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto exprValue = expr->getIRValue(metadata);
    const auto valueType = exprValue->getType();
    IRValue = exprValue;
    if (valueType->isPointerTy() || valueType->isVoidTy()) return;
    const auto ptr = builder.CreateAlloca(valueType);
    builder.CreateStore(exprValue, ptr);
}

Value* LgsVarDec::getIRValue(CodeGenMetadata* metadata) const {
    if (IRValue) return IRValue;
    assert(expr);
    return expr->getIRValue(metadata);
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

