#include "exprs/constants/LgsFloatConst.h"
#include "LgsType.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsAny.h"

Value* LgsFloatConst::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

LgsExpr* LgsFloatConst::castExplicitly(LgsType* toType) {
    if (type->getName() == toType->getName()) return this;
    if (toType->getName() == LgsAny::name) return this;
    if (toType->asDouble()) {
        // Widening is always allowed
        if (type->asFloat()) {
            setType(toType);
        }
        return this;
    }
    return nullptr;
}

void LgsFloatConst::castImplicitly(LgsType* toType) {
    const auto otherName = toType->getName();
    if (type->getName() == otherName) return;
    if (toType->isAny()) return;
    if (type->asFloat() && toType->asDouble()) {
        // Widening is always allowed
        setType(toType);
    }
}

std::string LgsFloatConst::asText() {
    return std::to_string(value);
}

void LgsFloatConst::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsFloatConst::clone() {
    return new LgsFloatConst(*this);
}
