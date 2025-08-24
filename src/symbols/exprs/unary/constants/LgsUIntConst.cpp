#include "exprs/unary/constants/LgsUIntConst.h"

#include "exprs/unary/constants/LgsStrConst.h"

std::string LgsUIntConst::pname() {
    return std::to_string(value);
}

json::value LgsUIntConst::asJSON() {
    assert(0);
}

Value* LgsUIntConst::eqIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::neIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::gtIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::ltIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::geIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::leIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::andIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {}
    assert(0);
}

Value* LgsUIntConst::orIR(LgsLLVM& codeGen, LgsExpr* other) {
    assert(0);
}

Value* LgsUIntConst::bitAndIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitOrIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitXorIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::rshiftIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::lshiftIR(LgsLLVM& codeGen, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return codeGen.builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(0);
}
