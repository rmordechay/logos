#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "utils/LgsUtils.h"

Value* LgsStrConst::hashValue(LgsModule* runtime) {
    return runtime->builder.getInt32(hashString(value));
}

Value* LgsStrConst::createIRValue(LgsModule* runtime) {
    return getIRStr(runtime, value);
}

Value* LgsStrConst::addIR(LgsModule* runtime, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return getIRStr(runtime, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return getIRStr(runtime, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asStrConst()) {
        return getIRStr(runtime, this->value + otherStrConst->value);
    }
    if (const auto otherBoolConst = other->asBoolConst()) {
        return getIRStr(runtime, this->value + otherBoolConst->getValueAsString());
    }
    assert(0);
}

Value* LgsStrConst::eqIR(LgsModule* runtime, LgsExpr* other) {
    return nullptr;
}
