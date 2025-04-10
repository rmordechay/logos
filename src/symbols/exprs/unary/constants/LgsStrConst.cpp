#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    return createGlobalStr(metadata->module, value);
}

size_t LgsStrConst::length() {
    return value.size();
}

LgsExpr* LgsStrConst::add(LgsExpr* other) {
    string otherValue;
    if (const auto intConst = other->asIntConst()) {
        otherValue = to_string(intConst->value);
    } else if (const auto floatConst = other->asFloatConst()) {
        otherValue = to_string(floatConst->value);
    } else if (const auto strConst = other->asStrConst()) {
        otherValue = this->value + strConst->value;
    }
    return new LgsStrConst(value + otherValue);
}

Value* LgsStrConst::sizeIR(CodeGenMetadata* metadata) {
    return metadata->builder.getInt32(value.size());
}

Value* LgsStrConst::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return createGlobalStr(metadata->module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return createGlobalStr(metadata->module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asStrConst()) {
        return createGlobalStr(metadata->module, this->value + otherStrConst->value);
    }
    return nullptr;
}

Value* LgsStrConst::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = other->asStrConst()) {
        const auto func = metadata->module->getOrInsertFunction("Str_compare_Str_Str", cmpStrIRFuncType);
        return metadata->builder.CreateCall(func, {getIRValue(metadata), otherStrConst->getIRValue(metadata)});
    }
    return nullptr;
}
