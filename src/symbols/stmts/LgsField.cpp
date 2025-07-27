#include "stmts/LgsField.h"

#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsHashMap.h"
#include "utils/LgsIRUtils.h"

Value* LgsField::getIRValue(LgsModule* module, LgsExpr* parentInstance) const {
    Value* value = nullptr;
    if (type->asEnum()) {
        value = expr ? expr->getIRValue(module) : getIRStr(module, name);
    } else if (isVirtual) {
        value = resolveVirtualField(module, parentInstance);
    } else {
        value = getGEP(module, parentInstance->getIRValue(module));
    }
    return value;
}

Value* LgsField::getGEP(LgsModule* module, Value* instance) const {
    return module->builder.CreateStructGEP(parentIRType, instance, position);
}

Value* LgsField::resolveVirtualField(LgsModule* module, LgsExpr* parentExpr) const {
    const auto vtable = parentExpr->type->vtable;
    const auto fieldIRType = type->getIRType(module);
    const auto vtableMap = vtable->type->asMap();
    const auto keyIR = getIRStr(module, name);
    const auto parentIRValue = parentExpr->getIRValue(module);
    const auto vtableIRType = vtable->type->getIRType(module);
    const auto mapPtr = module->builder.CreateGEP(vtableIRType, parentIRValue, {i64Zero(module)});
    const auto rv = vtableMap->getFunc.callIR(module, {mapPtr, keyIR});
    return module->builder.CreateLoad(fieldIRType, rv);
}

void LgsField::storeIRValue(LgsModule* module, Value* instance, LgsExpr* value) {
    const auto exprIRValue = value->getIRValue(module);
    // if (value->type->isPrimitive) {
    //     exprIRValue = module->builder.CreateLoad(value->type->getIRType(module), exprIRValue);
    // }
    module->builder.CreateStore(exprIRValue, instance);
}

LgsField* LgsField::clone() const {
    const auto cloned = new LgsField(name, parentName, type, expr);
    cloned->position = position;
    cloned->isPublic = isPublic;
    cloned->isVirtual = isVirtual;
    cloned->isOptional = isOptional;
    return cloned;
}

LgsField::~LgsField() {
    if (expr) delete expr;
}
