#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"

void LgsIntConst::createIRValue(LgsCodeGen* codeGen) {
    if (type->asBool()) {
        IRValue = codeGen->i1(value);
    } else if (type->asChar()) {
        IRValue = codeGen->i8(value);
    } else if (type->asShort()) {
        IRValue = codeGen->i16(value);
    } else if (type->asInt()) {
        IRValue = codeGen->i32(value);
    } else if (type->asLong()) {
        IRValue = codeGen->i64(value);
    }
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
    return type->getName() + "(" + std::to_string(value) + ")";
}

json::value LgsIntConst::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "intConst";
    jsonObj["name"] = pname();
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}
