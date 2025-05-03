#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

Value* LgsIntConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt32(value);
}

LgsExpr* LgsIntConst::castStatically(LgsType* other) {
    if (dynamic_cast<LgsStr*>(other)) {
        return new LgsStrConst(to_string(value));
    }
    return nullptr;
}

Value* LgsIntConst::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::neIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::gtIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::ltIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::geIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::leIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::andIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {

    }
    assert(false);
}

Value* LgsIntConst::orIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsIntConst::bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(false);
}