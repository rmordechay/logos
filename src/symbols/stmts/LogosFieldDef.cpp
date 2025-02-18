#include "stmts/LogosFieldDef.h"

#include "exprs/LogosInstance.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"
#include "stmts/LogosVarDec.h"

#include <LogosStack.h>

Value* LogosFieldDefinition::computeIRValue(CodeGenMetadata* metadata) {
    // TODO make dynamic
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto instance = metadata->logosStack->getSymbol(firstName)->instance;
    const auto obj = instance->obj;
    const auto value = instance->writeIRValue(metadata);
    const auto type = instance->type->getIRType();
    const auto fieldPos = obj->fields[secondName]->fieldPosition;
    const auto exprValue = expr->writeIRValue(metadata);
    const auto builder = metadata->builder;
    const auto gep = builder->CreateStructGEP(type, value, fieldPos);
    builder->CreateStore(exprValue, gep);
    return gep;
}

LogosFieldDefinition::~LogosFieldDefinition() {
    delete expr;
}
