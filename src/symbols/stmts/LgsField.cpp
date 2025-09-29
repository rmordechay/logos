#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsHashMap.h"
#include "types/iterables/LgsDArray.h"

Value* LgsField::loadIR(LgsLLVMGen& cg) {
    if (!IRValue) {
        IRValue = cg.builder.CreateStructGEP(parentIRType, parentIRValue, position);
    }
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

Value* LgsField::resolveVirtualField(LgsLLVMGen* cg, const LgsHashMap* vtable) const {
    const auto vtableMap = vtable->type->asMap();
    const auto fieldIRType = type->getIRType(*cg);
    const auto keyIR = cg->getIRStr(name);
    const auto vtableIRType = vtable->type->getIRType(*cg);
    const auto mapPtr = cg->builder.CreateGEP(vtableIRType, parentIRValue, {cg->i64Zero()});
    const auto rv = vtableMap->getIRElement(*cg, mapPtr, keyIR);
    return cg->builder.CreateLoad(fieldIRType, rv);
}

json::value LgsField::asJsonStr() {
    json::object obj;
    obj["name"] = name;
    obj["type"] = type->asJsonStr();
    return obj;
}

LgsField::~LgsField() {
    if (expr) {
        freeExpr(expr);
        expr = nullptr;
    }
}
