#include "exprs/unary/constants/LgsUIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "utils/LgsUtils.h"

string LgsUIntConst::prettyName() {
    return to_string(value);
}

Value* LgsUIntConst::createIRValue(LgsModule* module) {
    return i32(module, value);
}

LgsExpr* LgsUIntConst::convertExpr(LgsType* toType) {
    if (toType->asUInt()) {
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

LgsExpr* LgsUIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsUIntConst::eqIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::neIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::gtIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::ltIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::geIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::leIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::andIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {}
    assert(0);
}

Value* LgsUIntConst::orIR(LgsModule* module, LgsExpr* other) {
    assert(0);
}

Value* LgsUIntConst::bitAndIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitOrIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitXorIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::lshiftIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::rshiftIR(LgsModule* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return module->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(0);
}
