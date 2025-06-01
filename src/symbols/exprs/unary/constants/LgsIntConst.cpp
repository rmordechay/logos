#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

string LgsIntConst::prettyName() {
    return to_string(value);
}

Value* LgsIntConst::createIRValue(Module* module) {
    return builder.getInt32(value);
}

LgsExpr* LgsIntConst::convertExpr(LgsType* other) {
    if (dynamic_cast<LgsStr*>(other)) {
        return new LgsStrConst(to_string(value));
    }
    assert(false);
}

Value* LgsIntConst::eqIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::neIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::gtIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::ltIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::geIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::leIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::andIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {

    }
    assert(false);
}

Value* LgsIntConst::orIR(Module* module, LgsExpr* other) {
    assert(false);
}

Value* LgsIntConst::bitAndIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitOrIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitXorIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::lshiftIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(false);
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsIntConst::rshiftIR(Module* module, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(module);
    const auto thisIRValue = getIRValue(module);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(false);
}
