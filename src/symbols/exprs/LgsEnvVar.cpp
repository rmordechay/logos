#include "exprs/LgsEnvVar.h"

#include "utils/LgsUtils.h"

Value* LgsEnvVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsEnvVar::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, '$' + name);
}

std::string LgsEnvVar::asText() {
    return name;
}
