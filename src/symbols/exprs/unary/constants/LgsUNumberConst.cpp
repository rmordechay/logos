#include "exprs/unary/constants/LgsUNumberConst.h"

#include "exprs/unary/constants/LgsStrConst.h"

std::string LgsUNumberConst::pname() {
    return std::to_string(value);
}

void LgsUNumberConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i32(value);
}

LgsExpr* LgsUNumberConst::castTo(LgsType* toType) {
    if (toType->asUInt()) {
        return this;
    }
    if (toType->asStr()) {
        return new LgsStrConst(std::to_string(value));
    }
    if (toType->asLong()) {
        return new LgsNumberConst(&LGS_LONG, value);
    }
    return nullptr;
}

LgsExpr* LgsUNumberConst::clone() {
    return new LgsNumberConst(&LGS_UINT, value);
}

Value* LgsUNumberConst::eqIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::neIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::gtIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::ltIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::geIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::leIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::andIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {}
    assert(0);
}

Value* LgsUNumberConst::orIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUNumberConst::bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUNumberConst::rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen->builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(0);
}
