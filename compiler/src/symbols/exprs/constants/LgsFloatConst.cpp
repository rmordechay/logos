#include "exprs/constants/LgsFloatConst.h"
#include "LgsType.h"
#include "codegen/LgsCgModule.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"

Value* LgsFloatConst::loadIR(LgsCgModule& cg) {
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

std::string LgsFloatConst::asText() {
    return std::to_string(value);
}
