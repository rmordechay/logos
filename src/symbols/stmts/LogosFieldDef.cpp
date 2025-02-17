#include "stmts/LogosFieldDef.h"

#include "exprs/LogosConstructor.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"
#include "stmts/LogosVarDec.h"

Value* LogosFieldDef::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto constructor = metadata->theStack->getSymbol(firstName)->constructor;
    const auto obj = constructor->obj;
    const auto value = constructor->getLLVMValue(metadata);
    const auto type = constructor->type->getLLVMType();
    const auto fieldPos = obj->fields[secondName]->fieldPosition;
    const auto exprValue = expr->getLLVMValue(metadata);
    const auto gep = metadata->builder->CreateStructGEP(type, value, fieldPos);
    metadata->builder->CreateStore(exprValue, gep);
    return gep;
}

LogosFieldDef::~LogosFieldDef() {
    delete expr;
}
