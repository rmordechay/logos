#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "utils/LgsUtils.h"

Value* LgsStrConst::createIRValue(LgsRuntime* runtime) {
    return getIRStr(runtime, value);
}

Value* LgsStrConst::addIR(LgsRuntime* runtime, LgsExpr* other) {
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
    assert(false);
}

Value* LgsStrConst::eqIR(LgsRuntime* runtime, LgsExpr* other) {
    return nullptr;
}
