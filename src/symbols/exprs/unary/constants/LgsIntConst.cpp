#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

string LgsIntConst::prettyName() {
    return to_string(value);
}

Value* LgsIntConst::createIRValue(CodegenMetadata* metadata) {
    return metadata->builder.getInt32(value);
}

LgsExpr* LgsIntConst::convertExpr(LgsType* other) {
    if (dynamic_cast<LgsStr*>(other)) {
        return new LgsStrConst(to_string(value));
    }
    assert(false);
}

Value* LgsIntConst::eqIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::neIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::gtIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::ltIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::geIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::leIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::andIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {

    }
    assert(false);
}

Value* LgsIntConst::orIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false);
}

Value* LgsIntConst::bitAndIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitOrIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::bitXorIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(false);
}

Value* LgsIntConst::lshiftIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(false);
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsIntConst::rshiftIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(false);
}
