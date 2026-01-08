#include "loops/LgsMetaVar.h"

#include "LgsType.h"
#include "codegen/LgsCgModule.h"

Value* LgsMetaVar::loadIR(LgsCgModule& cg) {
    if (type->passByRef) return cg.load(cg.ptrTy(), IRValue);
    return cg.load(type->getIRType(cg), IRValue);
}

bool LgsMetaVar::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsMetaVar::asText() {
    return name;
}

void LgsMetaVar::setDebugValue(LgsCgModule& cg) {
    assert(0);
}
