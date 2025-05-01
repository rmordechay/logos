#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    return createIRStr(metadata->module, value);
}

Value* LgsStrConst::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return createIRStr(metadata->module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return createIRStr(metadata->module, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asStrConst()) {
        return createIRStr(metadata->module, this->value + otherStrConst->value);
    }
    return nullptr;
}

bool LgsStrConst::isIterable() {
    return true;
}

Value* LgsStrConst::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = other->asStrConst()) {
        const auto func = metadata->module->getOrInsertFunction("Str_compare_Str_Str", cmpStrIRFuncType);
        return metadata->builder.CreateCall(func, {getIRValue(metadata), otherStrConst->getIRValue(metadata)});
    }
    return nullptr;
}
