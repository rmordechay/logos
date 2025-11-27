#include "exprs/LgsEnvVar.h"

#include "LgsUtils.h"

Value* LgsEnvVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsEnvVar::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

void LgsEnvVar::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, '$' + name);
}

std::string LgsEnvVar::asText() {
    return name;
}
