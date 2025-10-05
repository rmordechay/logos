#include "symbols/types/LgsVoid.h"
#include "codegen/LgsLLVMGen.h"

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

Lgs_RTType LgsVoid::getRTType() {
    return RTT_VOID;
}

std::string LgsVoid::strFormatPart() const {
    assert(0);
}

bool LgsVoid::canCastTo(LgsType* other) {
    return name == other->getName();
}

json::value LgsVoid::asJsonStr() {
    return name;
}
