#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsHashMap.h"
#include "types/iterables/LgsDArray.h"

Value* LgsField::loadIR(LgsLLVMGen& cg) {
    if (!IRValue) {
        IRValue = cg.builder.CreateStructGEP(parentIRType, parentIRValue, position);
    }
    if (type->isPrimitive || type->asVec()) {
        return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
    }
    return cg.builder.CreateLoad(cg.ptrTy(), IRValue);
}

Value* LgsField::resolveVirtualField(LgsLLVMGen* cg, const LgsHashMap* vtable) const {
    const auto vtableMap = vtable->type->asMap();
    const auto fieldIRType = type->getIRType(*cg);
    const auto keyIR = cg->getIRStr(name);
    const auto vtableIRType = vtable->type->getIRType(*cg);
    const auto mapPtr = cg->builder.CreateGEP(vtableIRType, parentIRValue, {cg->i64Zero()});
    const auto rv = vtableMap->getFunc->callIR(*cg, {mapPtr, keyIR});
    return cg->builder.CreateLoad(fieldIRType, rv);
}

json::value LgsField::asJSON() {
    json::object obj;
    obj["name"] = name;
    obj["type"] = type->asJSON();
    return obj;
}

LgsField* LgsField::clone() const {
    const auto newField = new LgsField(*this);
    if (expr) {
        newField->expr = expr->clone();
    }
    return newField;
}

LgsField::~LgsField() {
    if (expr) {
        freeExpr(expr);
        expr = nullptr;
    }
}
