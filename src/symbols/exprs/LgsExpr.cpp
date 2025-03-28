#include "exprs/LgsExpr.h"

#include "exprs/unary/LgsArray.h"
#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsTypeConst.h"

Value* LgsExpr::getIRValue(CodeGenMetadata* metadata) {
    if (IRValue) return IRValue;
    IRValue = createIRValue(metadata);
    return IRValue;
}

LgsArray* LgsExpr::asArray() {
    return dynamic_cast<LgsArray*>(this);
}

LgsArrayIndex* LgsExpr::asArrayIndex() {
    return dynamic_cast<LgsArrayIndex*>(this);
}

LgsFuncCall* LgsExpr::asFuncCall() {
    return dynamic_cast<LgsFuncCall*>(this);
}

LgsInstance* LgsExpr::asInstance() {
    return dynamic_cast<LgsInstance*>(this);
}

LgsSelection* LgsExpr::asSelection() {
    return dynamic_cast<LgsSelection*>(this);
}

LgsVariable* LgsExpr::asVariable() {
    return dynamic_cast<LgsVariable*>(this);
}

LgsBoolConst* LgsExpr::asBoolConst() {
    return dynamic_cast<LgsBoolConst*>(this);
}

LgsCharConst* LgsExpr::asCharConst() {
    return dynamic_cast<LgsCharConst*>(this);
}

LgsFloatConst* LgsExpr::asFloatConst() {
    return dynamic_cast<LgsFloatConst*>(this);
}

LgsIntConst* LgsExpr::asIntConst() {
    return dynamic_cast<LgsIntConst*>(this);
}

LgsStrConst* LgsExpr::asStrConst() {
    return dynamic_cast<LgsStrConst*>(this);
}

LgsTypeConst* LgsExpr::asTypeConst() {
    return dynamic_cast<LgsTypeConst*>(this);
}

Value* LgsExpr::sub(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateSub(l, r);
}

Value* LgsExpr::mul(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateMul(l, r);
}

Value* LgsExpr::div(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateSDiv(l, r);
}