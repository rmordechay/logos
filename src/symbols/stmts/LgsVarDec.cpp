#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsDArray.h"

string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

void LgsVarDec::createIRStmt(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    assert(expr);
    const auto exprValue = expr->getIRValue(metadata);
    const auto valueType = exprValue->getType();
    // Pointers don't need to be stored
    if (!(valueType->isPointerTy() || valueType->isVoidTy())) {
        const auto ptr = builder.CreateAlloca(valueType);
        builder.CreateStore(exprValue, ptr);
    }
    IRValue = exprValue;
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

