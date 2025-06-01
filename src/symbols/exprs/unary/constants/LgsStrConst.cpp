#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

Value* LgsStrConst::getLength(Module* module) {
    return builder.getInt32(value.size());
}

Value* LgsStrConst::createIRValue(Module* module) {
    return getIRStr(module, value);
}

Value* LgsStrConst::addIR(Module* module, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return getIRStr(module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return getIRStr(module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asStrConst()) {
        return getIRStr(module, this->value + otherStrConst->value);
    }
    if (const auto otherBoolConst = other->asBoolConst()) {
        return getIRStr(module, this->value + otherBoolConst->getValueAsString());
    }
    assert(false);
}

Value* LgsStrConst::eqIR(Module* module, LgsExpr* other) {
    return nullptr;
}
