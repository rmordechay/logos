#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsHashMap.h"

Value* LgsField::getIRValue(LgsCodeGen* codeGen, LgsExpr* parentInstance) {
    if (IRValue) return IRValue;
    if (type->asEnum()) {
        IRValue = expr ? expr->getIRValue(codeGen) : codeGen->getIRStr(name);
    } else if (isVirtual) {
        IRValue = resolveVirtualField(codeGen, parentInstance);
    } else {
        IRValue = getGEP(codeGen, parentInstance->getIRValue(codeGen));
    }
    return IRValue;
}

Value* LgsField::getGEP(LgsCodeGen* codeGen, Value* instance) const {
    return codeGen->builder.CreateStructGEP(parentIRType, instance, position);
}

Value* LgsField::resolveVirtualField(LgsCodeGen* codeGen, LgsExpr* parentExpr) const {
    const auto vtable = parentExpr->type->vtable;
    const auto fieldIRType = type->getIRType(codeGen);
    const auto vtableMap = vtable->type->asMap();
    const auto keyIR = codeGen->getIRStr(name);
    const auto parentIRValue = parentExpr->getIRValue(codeGen);
    const auto vtableIRType = vtable->type->getIRType(codeGen);
    const auto mapPtr = codeGen->builder.CreateGEP(vtableIRType, parentIRValue, {codeGen->i64Zero()});
    const auto rv = vtableMap->getFunc.callIR(codeGen, {mapPtr, keyIR});
    return codeGen->builder.CreateLoad(fieldIRType, rv);
}

void LgsField::storeIRValue(LgsCodeGen* codeGen, Value* instance, LgsExpr* value) {
    const auto exprIRValue = value->getIRValue(codeGen);
    codeGen->builder.CreateStore(exprIRValue, instance);
}

LgsField* LgsField::clone() const {
    const auto cloned = new LgsField(*this);
    cloned->position = position;
    cloned->isPublic = isPublic;
    cloned->isVirtual = isVirtual;
    cloned->isOptional = isOptional;
    return cloned;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
