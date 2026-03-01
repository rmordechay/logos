#include "stmts/LgsField.h"

#include <assert.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include "LgsType.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsExpr.h"

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
    IRValue = cg.builder.CreateStructGEP(ty, parentIRPtr, index);
    return IRValue;
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
