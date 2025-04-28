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