#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "utils/LgsUtils.h"

extern "C" {
    size_t Str_hash(const char* key);
}

Value* LgsStrConst::hashValue(LgsModule* module) {
    return module->builder.getInt32(Str_hash(value.c_str()));
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
