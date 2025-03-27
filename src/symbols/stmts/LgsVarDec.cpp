#include "stmts/LgsVarDec.h"

#include "exprs/unary/LgsArray.h"
#include "exprs/unary/constants/LgsConstExpr.h"
#include <LgsStack.h>
#include <json/json.hpp>

Value* LgsVarDec::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    if (!expr) return builder.CreateAlloca(type->getIRType());

    const auto exprValue = expr->getIRValue(metadata);
    const auto valueType = exprValue->getType();
    // Pointers don't need to be stored
    if (!valueType->isPointerTy()) {
        const auto ptr = builder.CreateAlloca(valueType);
        builder.CreateStore(exprValue, ptr);
    }
    metadata->logosStack.addLocalSymbol(name, this);
    IRValue = exprValue;
    return exprValue;
}

void LgsVarDec::free(CodeGenMetadata* metadata) {
    if (const auto arr = dynamic_cast<LgsArray*>(expr)) {
        arr->free(metadata);
    }
}

json LgsVarDec::asJson() {
    json tree;
    tree["stmtType"] = "varDec";
    if (type) {
        tree["type"] = type->getName();
    }
    if (expr) {
        tree["expr"] = expr->asJson();
    }
    return tree;
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}

