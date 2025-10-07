#include "symbols/types/LgsVoid.h"
#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

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

Lgs_rttype LgsVoid::getRTType() {
    return RTT_VOID;
}

std::string LgsVoid::strFormatPart() const {
    assert(0);
}

bool LgsVoid::canCastTo(LgsType* other) {
    return name == other->getName();
}

void LgsVoid::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "name", name);
    closeJsonObject(json);
}
