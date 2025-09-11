#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

Value* LgsIntConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::castTo(LgsType* toType) {
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

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(*this);
}

std::string LgsIntConst::pname() {
    return std::to_string(value);
}

json::value LgsIntConst::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "intConst";
    jsonObj["name"] = pname();
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}
