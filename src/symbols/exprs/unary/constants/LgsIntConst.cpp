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
    return LgsConstExpr::eqIR(metadata, other);
}

Value* LgsIntConst::neIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::neIR(metadata, other);
}

Value* LgsIntConst::gtIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::gtIR(metadata, other);
}

Value* LgsIntConst::ltIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::ltIR(metadata, other);
}

Value* LgsIntConst::geIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::geIR(metadata, other);
}

Value* LgsIntConst::leIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::leIR(metadata, other);
}

Value* LgsIntConst::andIR(CodeGenMetadata* metadata, LgsExpr* right) {
    return LgsConstExpr::andIR(metadata, right);
}

Value* LgsIntConst::orIR(CodeGenMetadata* metadata, LgsExpr* right) {
    return LgsConstExpr::orIR(metadata, right);
}

Value* LgsIntConst::bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::leIR(metadata, other);
}

Value* LgsIntConst::bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateOr(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::bitOrIR(metadata, other);
}

Value* LgsIntConst::bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateXor(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::bitXorIR(metadata, other);
}

Value* LgsIntConst::lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateShl(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::lshiftIR(metadata, other);
}

Value* LgsIntConst::rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(metadata);
    const auto thisIRValue = getIRValue(metadata);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return metadata->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    return LgsConstExpr::rshiftIR(metadata, other);
}