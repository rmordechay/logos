#include "stmts/LogosFieldDef.h"

#include "exprs/LogosInstance.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"
#include "stmts/LogosVarDec.h"

Value* LogosFieldDef::computeIRValue(CodeGenMetadata* metadata) {
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto instance = metadata->theStack->getSymbol(firstName)->instance;
    const auto obj = instance->obj;
    const auto value = instance->getIRValue(metadata);
    const auto type = instance->type->getIRType();
    const auto fieldPos = obj->fields[secondName]->fieldPosition;
    const auto exprValue = expr->getIRValue(metadata);
    const auto gep = metadata->builder->CreateStructGEP(type, value, fieldPos);
    metadata->builder->CreateStore(exprValue, gep);
    return gep;
}

LogosFieldDef::~LogosFieldDef() {
    delete expr;
}
