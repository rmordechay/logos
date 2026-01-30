#include "exprs/constants/LgsCharConst.h"

#include "codegen/LgsCodeGen.h"

Value* LgsCharConst::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

void LgsCharConst::castImplicitly(LgsType* toType) {

}

std::string LgsCharConst::asText() {
    return type->pname();
}

void LgsCharConst::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}
