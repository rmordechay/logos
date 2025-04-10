#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

Value* LgsIntConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt32(value);
}

LgsExpr* LgsIntConst::add(LgsExpr* other) {
    if (const auto intConst = other->asIntConst()) {
        return new LgsIntConst(value + intConst->value);
    }
    if (const auto floatConst = other->asFloatConst()) {
        return new LgsFloatConst(value + floatConst->value);
    }
    if (const auto strConst = other->asStrConst()) {
        return strConst->add(this);
    }
    return nullptr;
}

LgsExpr* LgsIntConst::castStatically(LgsType* other) {
    if (dynamic_cast<LgsStr*>(other)) {
        return new LgsStrConst(to_string(value));
    }
    return nullptr;
}
