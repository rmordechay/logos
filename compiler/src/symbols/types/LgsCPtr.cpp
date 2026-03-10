#include "types/LgsCPtr.h"

#include <assert.h>
#include <llvm/IR/DerivedTypes.h>

#include "types/primitives/LgsAny.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsLong.h"
#include "codegen/LgsCodeGen.h"

std::string LgsCPtr::getName() {
    return name;
}

std::string LgsCPtr::pname() {
    return name;
}

Type* LgsCPtr::getIRType(LgsCodeGen& cg) {
    return cg.ptrTy();
}

size_t LgsCPtr::sizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsCPtr::getZeroValue() {
    assert(0);
}

bool LgsCPtr::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsSArray::name) return true;
    if (IRName == LgsDArray::name) return true;
    return name == IRName;
}

LgsType* LgsCPtr::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsCPtr::fmtStr() const {
    return baseType->fmtStr();
}

DIType* LgsCPtr::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsCPtr::~LgsCPtr() {
    freeType(baseType);
    baseType = nullptr;
}
