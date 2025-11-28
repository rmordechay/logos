#include "types/primitives/LgsVoid.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsFuncType.h"

#include <llvm/IR/DIBuilder.h>

Type* LgsVoid::getIRType(LgsCgModule& cg) {
    return Type::getVoidTy(cg.context);
}

Constant* LgsVoid::getRTType(LgsCgModule& cg) {
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

llvm::DIType* LgsVoid::getDebugType(LgsCgModule& cg) {
    return cg.debugger.diBuilder->createUnspecifiedType(name);
}