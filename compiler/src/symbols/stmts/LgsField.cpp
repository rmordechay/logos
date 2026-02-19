#include "stmts/LgsField.h"
#include "LgsType.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsHashMap.h"

void LgsField::setType(LgsType* newType) {
    type = newType;
}

LgsType* LgsField::getType() {
    return type;
}

Value* LgsField::loadIRPtr(LgsCodeGen& cg, Value* ptr) const {
    if (!ptr->getType()->isPointerTy()) return ptr;
    if (type->asSArray()) return ptr;
    if (type->asNullable() && !type->passByRef) return ptr;
    return cg.load(type->getStorageType(cg), ptr);
}

Value* LgsField::getGEP(LgsCodeGen& cg, Value* parentIRPtr) {
    assert(parentType && parentIRPtr);
    const auto ty = parentType->getIRType(cg);
    if (parentType->asVec()) {
        gep = cg.builder.CreateGEP(ty, parentIRPtr, {cg.zero32(), cg.i32(index)});
    } else {
        gep = cg.builder.CreateStructGEP(ty, parentIRPtr, index);
    }
    return gep;
}

void LgsField::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsField::~LgsField() {
    freeExpr(expr);
    freeType(type);
    expr = nullptr;
    type = nullptr;
}
