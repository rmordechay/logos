#include "exprs/constants/LgsCharConst.h"

#include "codegen/LgsCgModule.h"

Value* LgsCharConst::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsCharConst::castImplicitly(LgsType* toType) {
    LgsExpr::castImplicitly(toType);
}

Value* LgsCharConst::hashValue(LgsCgModule& cg) {
    return cg.extendToSize(IRValue);
}

std::string LgsCharConst::asText() {
    return type->pname();
}

void LgsCharConst::setDebugValue(LgsCgModule& cg) {
    assert(0);
}
