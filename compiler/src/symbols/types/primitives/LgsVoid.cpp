#include "types/primitives/LgsVoid.h"
#include "codegen/LgsLLVMGen.h"
#include "types/LgsFuncType.h"

#include <llvm/IR/DIBuilder.h>

Type* LgsVoid::getIRType(LgsLLVMGen& cg) {
    return Type::getVoidTy(cg.context);
}

Constant* LgsVoid::getRTType(LgsLLVMGen& cg) {
    assert(0);
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

std::string LgsVoid::strFormatPart() const {
    assert(0);
}

bool LgsVoid::canCastTo(LgsType* other) {
    return name == other->getName();
}

llvm::DIType* LgsVoid::getDebugType(LgsLLVMGen& cg) {
    return cg.debugger.diBuilder->createUnspecifiedType(name);
}

LgsType* LgsVoid::clone() {
    return this;
}
