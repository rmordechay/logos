#include "types/primitives/LgsVoid.h"
#include "codegen/LgsLLVMGen.h"
#include "types/LgsFuncType.h"

#include <llvm/IR/DIBuilder.h>

Type* LgsVoid::getIRType(LgsLLVMGen& cg) {
    return Type::getVoidTy(cg.context);
}

size_t LgsVoid::getSizeBytes() {
    return 0;
}

std::string LgsVoid::getName() {
    return name;
}

LgsExpr* LgsVoid::getZeroValue() {
    return nullptr;
}

Lgs_TypeKind LgsVoid::getRTTypeKind() {
    return RTT_VOID;
}

std::string LgsVoid::strFormatPart() const {
    assert(0);
}

bool LgsVoid::canCastTo(LgsType* other) {
    if (const auto funcType = other->asFuncType()) {
        return funcType->params.empty() && funcType->rt->isVoid();
    }
    return name == other->getName();
}

DIBasicType* LgsVoid::getDebugType(LgsLLVMGen& cg) {
    return cg.debugger.diBuilder->createUnspecifiedType(name);
}
