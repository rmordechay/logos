#include "types/LgsPtr.h"

#include "codegen/LgsCodeGen.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsLong.h"

std::string LgsPtr::getName() {
    return name;
}

std::string LgsPtr::pname() {
    return name;
}

Type* LgsPtr::getIRType(LgsCgModule& cg) {
    return cg.ptrTy();
}

Constant* LgsPtr::getRTType(LgsCgModule& cg) {
    assert(0);
}

size_t LgsPtr::sizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsPtr::getZeroValue() {
    assert(0);
}

bool LgsPtr::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsSArray::name) return true;
    if (IRName == LgsDArray::name) return true;
    return name == IRName;
}

LgsType* LgsPtr::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

std::string LgsPtr::fmtStr() const {
    return baseType->fmtStr();
}

DIType* LgsPtr::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsPtr::~LgsPtr() {
    freeType(baseType);
    baseType = nullptr;
}
