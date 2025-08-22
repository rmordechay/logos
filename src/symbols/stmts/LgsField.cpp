#include "stmts/LgsField.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsHashMap.h"

void LgsField::createIRValue(LgsCodeGen* codeGen) {
    if (parentIRType->isVectorTy()) {
        const auto vec = codeGen->builder.CreateLoad(parentIRType, parentIRValue);
        const auto i = codeGen->isize(position);
        IRValue = codeGen->builder.CreateExtractElement(vec, i);
    } else {
        IRValue = codeGen->builder.CreateStructGEP(parentIRType, parentIRValue, position);
    }
}

Value* LgsField::resolveVirtualField(LgsCodeGen* codeGen, const LgsHashMap* vtable) const {
    const auto vtableMap = vtable->type->asMap();
    const auto fieldIRType = type->getIRType(codeGen);
    const auto keyIR = codeGen->getIRStr(name);
    const auto vtableIRType = vtable->type->getIRType(codeGen);
    const auto mapPtr = codeGen->builder.CreateGEP(vtableIRType, parentIRValue, {codeGen->i64Zero()});
    const auto rv = vtableMap->getFunc->callIR(codeGen, {mapPtr, keyIR});
    return codeGen->builder.CreateLoad(fieldIRType, rv);
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
