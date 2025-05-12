#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    for (auto& global : metadata->module->globals()) {
        if (!global.isConstant() || !global.hasInitializer()) continue;
        const auto* dataArray = dyn_cast<ConstantDataArray>(global.getInitializer());
        if (!dataArray || !dataArray->isString()) continue;
        if (dataArray->getAsString().str().c_str() == value) return &global;
    }
    return getIRStr(metadata->module, value);
}

Value* LgsStrConst::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
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

Value* LgsStrConst::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    return nullptr;
}
