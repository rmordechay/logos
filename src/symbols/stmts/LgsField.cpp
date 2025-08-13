#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsHashMap.h"

Value* LgsField::getGEP(LgsCodeGen* codeGen, Value* parentIRValue) const {
    return codeGen->builder.CreateStructGEP(parentIRType, parentIRValue, position);
}

Value* LgsField::resolveVirtualField(LgsCodeGen* codeGen, const LgsHashMap* vtable, Value* parentIRValue) const {
    const auto vtableMap = vtable->type->asMap();
    const auto fieldIRType = type->getIRType(codeGen);
    const auto keyIR = codeGen->getIRStr(name);
    const auto vtableIRType = vtable->type->getIRType(codeGen);
    const auto mapPtr = codeGen->builder.CreateGEP(vtableIRType, parentIRValue, {codeGen->i64Zero()});
    const auto rv = vtableMap->getFunc.callIR(codeGen, {mapPtr, keyIR});
    return codeGen->builder.CreateLoad(fieldIRType, rv);
}

LgsField::~LgsField() {
    if (expr) {
        delete expr;
        expr = nullptr;
    }
}
