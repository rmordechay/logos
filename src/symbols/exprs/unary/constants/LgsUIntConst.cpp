#include "exprs/unary/constants/LgsUIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

#include "utils/LgsUtils.h"

std::string LgsUIntConst::prettyName() {
    return std::to_string(value);
}

void LgsUIntConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i32(value);
}

LgsExpr* LgsUIntConst::castTo(LgsType* toType) {
    if (toType->asUInt()) {
        return this;
    }
    if (toType->asStr()) {
        return new LgsStrConst(std::to_string(value));
    }
    if (toType->asLong()) {
        return new LgsLongConst(value);
    }
    return nullptr;
}

LgsExpr* LgsUIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsUIntConst::eqIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::neIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::gtIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::ltIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::geIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::leIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::andIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {}
    assert(0);
}

Value* LgsUIntConst::orIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUIntConst::bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(0);
}
