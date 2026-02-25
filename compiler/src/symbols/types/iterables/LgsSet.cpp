#include "types/iterables/LgsSet.h"

#include <assert.h>
#include <llvm/IR/DerivedTypes.h>

#include "LgsBinaryTokens.h"
#include "codegen/LgsCodeGen.h"
#include "LgsType.h"

Type* LgsSet::getIRType(LgsCodeGen& cg) {
    return cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy()}, name);
}

size_t LgsSet::sizeBytes() {
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsSet::getZeroValue() {
    assert(0);
}

std::string LgsSet::getBaseName() {
    return name;
}

std::string LgsSet::getName() {
    return name;
}

std::string LgsSet::pname() {
    return std::string(name);
}

bool LgsSet::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    const auto otherArr = other->asSet();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

std::string LgsSet::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSet::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    const auto IRName = rightType->getName();
    switch (op.opType) {
    case IN: {
        if (rightType->canCastTo(baseType)) return baseType;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsSet::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.callLgsFunc(name, "len", cg.sizeTy(), {cg.ptrTy()}, {iterable});
}

Value* LgsSet::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    assert(0);
}

Value* LgsSet::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    assert(0);
}

DIType* LgsSet::getDebugType(LgsCodeGen& cg) {
    assert(0);
}