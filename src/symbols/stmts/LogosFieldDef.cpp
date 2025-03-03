#include "stmts/LogosAssignment.h"

#include "exprs/LogosInstance.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"
#include "stmts/LogosVarDec.h"

#include <LogosStack.h>
#include <types/LogosInt.h>

Value* LogosAssignment::computeIRValue(CodeGenMetadata* metadata) {
    // TODO make dynamic
    auto& builder = metadata->builder;
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto instance = metadata->logosStack.getSymbol(firstName)->instance;

    const auto obj = instance->obj;
    const auto objValue = instance->writeIRValue(metadata);
    const auto objType = instance->type->getIRType();

    const auto fieldPos = obj->fields[secondName]->fieldPosition;
    const auto fieldExprValue = expr->writeIRValue(metadata);
    obj->fields[secondName]->expr = expr;
    const auto gep = builder.CreateStructGEP(objType, objValue, fieldPos);
    builder.CreateStore(fieldExprValue, gep);
    return gep;
}

LogosAssignment::~LogosAssignment() {
    delete expr;
}
