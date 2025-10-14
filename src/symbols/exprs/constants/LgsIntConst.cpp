#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"

Value* LgsIntConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::castTo(LgsType* toType, const bool explicitCast) {
    if (toType->getName() == LgsAny::name) return this;
    if (type->getName() == toType->getName()) return this;
    if (toType->asLong()) {
        type = &LGS_LONG;
        return this;
    }
    if (toType->asSize()) {
        type = &LGS_SIZE;
        return this;
    }
    if (toType->asFloat()) {
        return new LgsFloatConst(&LGS_FLOAT, value);
    }
    if (toType->asDouble()) {
        return new LgsFloatConst(&LGS_DOUBLE, value);
    }
    if (explicitCast && toType->asStr()) {
        return new LgsStrConst(std::to_string(value));
    }
    assert(0);
}

Value* LgsIntConst::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(IRValue);
    if (type->getName() == toType->getName()) return IRValue;
    if (toType->asLong()) {
        return cg.i64(value);
    }
    if (toType->asSize()) {
        return cg.usize(value);
    }
    if (toType->asFloat()) {
        return cg.floatv(value);
    }
    if (toType->asDouble()) {
        return cg.doublev(value);
    }
    if (toType->asStr()) {
        return cg.getIRStr(std::to_string(value));
    }
    assert(0);
}

void LgsIntConst::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "kind", "IntConst", true);
    addJsonKeyValue(json, "value", value);
    closeJsonObject(json);
}

std::string LgsIntConst::getName() {
    return std::to_string(value);
}

Value* LgsIntConst::hash(LgsLLVMGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(type->clone(), value);
}
