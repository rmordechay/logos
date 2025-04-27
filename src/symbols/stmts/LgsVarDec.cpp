#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArray.h"

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

Value* LgsVarDec::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    if (!expr) return builder.CreateAlloca(type->getIRType());

    const auto exprValue = expr->getIRValue(metadata);
    const auto valueType = exprValue->getType();
    // Pointers don't need to be stored
    if (!(valueType->isPointerTy() || valueType->isVoidTy())) {
        const auto ptr = builder.CreateAlloca(valueType);
        builder.CreateStore(exprValue, ptr);
    }
    IRValue = exprValue;
    return exprValue;
}

json LgsVarDec::asJSON() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->getName();
    tree["stmtType"] = "VAR_DEC";
    return tree;
}

void LgsVarDec::free(CodeGenMetadata* metadata) {
    expr->free(metadata);
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}

