#include "stmts/LgsVarDec.h"
#include "constants/LgsConst.h"
#include <LgsStack.h>
#include <json/json.hpp>

Value* LgsVarDec::createIRValue(CodeGenMetadata* metadata) {
    Value* exprValue;
    if (expr) {
        exprValue = expr->getIRValue(metadata);
    } else {
        exprValue = type->getZeroValue()->getIRValue(metadata);
    }
    const auto valueType = exprValue->getType();
    if (!valueType->isPointerTy()) {
        auto& builder = metadata->builder;
        const auto allocaInst = builder.CreateAlloca(valueType);
        builder.CreateStore(exprValue, allocaInst);
    }
    metadata->logosStack.addLocalSymbol(name, this);
    return exprValue;
}

json LgsVarDec::asJson() {
    stringstream str;
    str << string(typeid(this).name()) << name;
    str << "Expr: " << expr->asJson();
    return str.str();
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}

