#include "stmts/LogosFieldDef.h"

#include "exprs/LogosConstructor.h"
#include "object/LogosObject.h"
#include "stmts/LogosVarDec.h"

Value* LogosFieldDef::getLLVMValue(CodeGenMetadata* metadata) {
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto varDec = metadata->theStack->getSymbol(firstName)->varDec;
    const auto objName = varDec->expr->asConstructor()->type->name();
    const auto obj = metadata->theStack->getSymbol(objName)->object;
    const auto fieldPos = obj->fields[secondName]->fieldPosition;
    const auto value = varDec->getLLVMValue(metadata);
    const auto type = varDec->inferredType->getLLVMType();
    llvmValue = metadata->builder->CreateStructGEP(type, value, fieldPos);
    return llvmValue;
}

LogosFieldDef::~LogosFieldDef() {
    delete expr;
}
