#include "exprs/LgsEnvVar.h"

#include "LgsUtils.h"

Value* LgsEnvVar::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

void LgsEnvVar::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, '$' + name);
}

std::string LgsEnvVar::asText() {
    return name;
}

void LgsEnvVar::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}
