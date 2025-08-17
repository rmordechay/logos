#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

#include "utils/LgsUtils.h"

std::string LgsIntConst::pname() {
    return std::to_string(value);
}

void LgsIntConst::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->i32(value);
}

LgsExpr* LgsIntConst::castImplicitly(LgsType* toType) {
    if (toType->asInt()) {
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

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(value);
}

Value* LgsIntConst::andIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    return codeGen->builder.CreateAnd(thisIRValue, otherIRValue);
}

Value* LgsIntConst::orIR(LgsCodeGen* codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsIntConst::bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    return codeGen->builder.CreateAnd(thisIRValue, otherIRValue);
}

Value* LgsIntConst::bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    return codeGen->builder.CreateOr(thisIRValue, otherIRValue);
}

Value* LgsIntConst::bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    return codeGen->builder.CreateXor(thisIRValue, otherIRValue);
}

Value* LgsIntConst::lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    return codeGen->builder.CreateShl(thisIRValue, otherIRValue);
}

Value* LgsIntConst::rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) {
    const auto otherIRValue = other->getIRValue(codeGen);
    const auto thisIRValue = getIRValue(codeGen);
    return codeGen->builder.CreateAShr(thisIRValue, otherIRValue);
}
