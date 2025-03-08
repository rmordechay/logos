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
    // const auto nextName = names[0];
    // const auto prevName = names[1];
    // const auto obj = metadata->logosStack.getSymbol(nextName)->object;

    // const auto objValue = obj->writeIRValue(metadata);
    // const auto objType = obj->type->getIRType();
    //
    // const auto fieldPos = obj->fields[prevName]->fieldPosition;
    // const auto fieldExprValue = expr->writeIRValue(metadata);
    // obj->fields[prevName]->expr = expr;
    // const auto gep = builder.CreateStructGEP(objType, objValue, fieldPos);
    // builder.CreateStore(fieldExprValue, gep);
    // return gep;
    return nullptr;
}

LogosAssignment::~LogosAssignment() {
    delete lvalue;
    delete rvalue;
}
