#include "stmts/LogosFieldDef.h"

#include "stmts/LogosVarDec.h"

Value* LogosFieldDef::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto varDec = metadata->theStack->getSymbol(firstName)->varDec;
    const auto exprValue = varDec->expr->llvmValue;
    return metadata->builder->CreateStructGEP(exprValue->getType(), exprValue, 0);
}

LogosFieldDef::~LogosFieldDef() {
    delete expr;
}
