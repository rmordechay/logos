#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

Value* LgsIntConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::castTo(LgsType* toType) {
    if (toType->getName() == LgsAny::name) return this;
    if (type->getName() == toType->getName()) return this;
    if (toType->asLong()) {
        return new LgsIntConst(&LGS_LONG, value);
    }
    if (toType->asFloat()) {
        return new LgsFloatConst(&LGS_FLOAT, value);
    }
    if (toType->asDouble()) {
        return new LgsFloatConst(&LGS_DOUBLE, value);
    }
    assert(0);
}

std::string LgsIntConst::getName() {
    return std::to_string(value);
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(type->clone(), value);
}

json::value LgsIntConst::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprType"] = "intConst";
    jsonObj["name"] = getName();
    jsonObj["type"] = type->asJsonStr();
    return jsonObj;
}
