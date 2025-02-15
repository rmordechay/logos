#include "stmts/LogosFieldDef.h"

#include "stmts/LogosVarDec.h"

Value* LogosFieldDef::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto varDec = metadata->theStack->getSymbol(firstName)->varDec;
    const auto expr = varDec->expr;
    const auto llvmValue = expr->llvmValue;
    // const auto llvmType = varDec->expr->type->getLLVMType();
    // const auto obj = metadata->theStack->getSymbol()->object;
    auto a = StructType::create(context);
    return metadata->builder->CreateStructGEP(a, llvmValue, 0);
}

LogosFieldDef::~LogosFieldDef() {
    delete expr;
}
