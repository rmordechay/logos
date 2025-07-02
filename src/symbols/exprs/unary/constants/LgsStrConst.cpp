#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "utils/LgsUtils.h"

Value* LgsStrConst::hashValue(LgsModule* module) {
    return module->builder.getInt32(hashString(value));
}

Value* LgsStrConst::createIRValue(LgsModule* module) {
    return getIRStr(module, value);
}

Value* LgsStrConst::addIR(LgsModule* module, LgsExpr* other) {
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
    assert(0);
}

Value* LgsStrConst::eqIR(LgsModule* module, LgsExpr* other) {
    return nullptr;
}
