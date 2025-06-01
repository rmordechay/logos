#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

Value* LgsStrConst::getLength(CodegenMetadata* metadata) {
    return metadata->builder.getInt32(value.size());
}

Value* LgsStrConst::createIRValue(CodegenMetadata* metadata) {
    return getIRStr(metadata->module, value);
}

Value* LgsStrConst::addIR(CodegenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return getIRStr(metadata->module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return getIRStr(metadata->module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asStrConst()) {
        return getIRStr(metadata->module, this->value + otherStrConst->value);
    }
    if (const auto otherBoolConst = other->asBoolConst()) {
        return getIRStr(metadata->module, this->value + otherBoolConst->getValueAsString());
    }
    assert(false);
}

Value* LgsStrConst::eqIR(CodegenMetadata* metadata, LgsExpr* other) {
    return nullptr;
}
