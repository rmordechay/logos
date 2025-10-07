#include "types/LgsUnknown.h"

#include "utils/LgsUtils.h"

std::string LgsUnknown::getName() {
    return name;
}

LgsExpr* LgsUnknown::getZeroValue() {
    assert(0);
}

Lgs_rttype LgsUnknown::getRTType() {
    return RTT_UNKNOWN;
}

size_t LgsUnknown::getSizeBytes() {
    return 0;
}

bool LgsUnknown::canCastTo(LgsType* other) {
    return false;
}

std::string LgsUnknown::strFormatPart() const {
    assert(0);
}

void LgsUnknown::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "name", name);
    closeJsonObject(json);
}

llvm::Type* LgsUnknown::getIRType(LgsLLVMGen& cg) {
    assert(0);
}
