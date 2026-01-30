#include "types/primitives/LgsVoid.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsFuncType.h"

#include <llvm/IR/DIBuilder.h>

Type* LgsVoid::getIRType(LgsCodeGen& cg) {
    return Type::getVoidTy(cg.context);
}

Constant* LgsVoid::getRTType(LgsCodeGen& cg) {
    return cg.getRTTypeInfo(getName(), cg.sizeZero(), RTT_VOID);
}

size_t LgsVoid::sizeBytes() {
    return 0;
}

std::string LgsVoid::getName() {
    return name;
}

LgsExpr* LgsVoid::getZeroValue() {
    return nullptr;
}

LgsType* LgsVoid::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsVoid::fmtStr() const {
    assert(0);
}

bool LgsVoid::canCastTo(LgsType* other) {
    return name == other->getName();
}

DIType* LgsVoid::getDebugType(LgsCodeGen& cg) {
    return cg.debugger.diBuilder->createUnspecifiedType(name);
}