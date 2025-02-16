#include "stmts/LogosFieldDef.h"

#include "exprs/LogosConstructor.h"
#include "object/LogosObject.h"
#include "stmts/LogosVarDec.h"

Value* LogosFieldDef::getLLVMValue(CodeGenMetadata* metadata) {
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto constructor = metadata->theStack->getSymbol(firstName)->constructor;
    const auto obj = constructor->obj;
    const auto value = constructor->getLLVMValue(metadata);
    const auto type = constructor->type->getLLVMType();
    const auto fieldPos = obj->fields[secondName]->fieldPosition;
    llvmValue = metadata->builder->CreateStructGEP(type, value, fieldPos);
    return llvmValue;
}

LogosFieldDef::~LogosFieldDef() {
    delete expr;
}
