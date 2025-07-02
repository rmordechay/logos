#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

string LgsIntConst::prettyName() {
    return to_string(value);
}

Value* LgsIntConst::createIRValue(LgsModule* module) {
    return module->builder.getInt32(value);
}

LgsExpr* LgsIntConst::convertExpr(LgsType* toType) {
    if (toType->asInt()) {
        return this;
    }
    if (toType->asStr()) {
        return new LgsStrConst(to_string(value));
    }
    if (toType->asLong()) {
        return new LgsLongConst(value);
    }
    assert(0);
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsIntConst::andIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    return module->builder.CreateAnd(thisIRValue, otherIRValue);
}

Value* LgsIntConst::orIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsIntConst::bitAndIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    return module->builder.CreateAnd(thisIRValue, otherIRValue);
}

Value* LgsIntConst::bitOrIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    return module->builder.CreateOr(thisIRValue, otherIRValue);
}

Value* LgsIntConst::bitXorIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    return module->builder.CreateXor(thisIRValue, otherIRValue);
}

Value* LgsIntConst::lshiftIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    return module->builder.CreateShl(thisIRValue, otherIRValue);
}

Value* LgsIntConst::rshiftIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    return module->builder.CreateAShr(thisIRValue, otherIRValue);
}
