#include "exprs/constants/LgsUIntConst.h"

#include "exprs/constants/LgsStrConst.h"

std::string LgsUIntConst::pname() {
    return std::to_string(value);
}

json::value LgsUIntConst::asJSON() {
    assert(0);
}

Value* LgsUIntConst::eqIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateICmpEQ(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::neIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateICmpNE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::gtIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateICmpSGT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::ltIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateICmpSLT(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::geIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateICmpSGE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::leIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateICmpSLE(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::andIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {}
    assert(0);
}

Value* LgsUIntConst::orIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsUIntConst::bitAndIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateAnd(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitOrIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateOr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::bitXorIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateXor(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::rshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateAShr(thisIRValue, otherIRValue);
    }
    assert(0);
}

Value* LgsUIntConst::lshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto otherIRValue = other->IRValue;
    const auto thisIRValue = IRValue;
    if (thisIRValue->getType()->isIntegerTy() && otherIRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateShl(thisIRValue, otherIRValue);
    }
    assert(0);
}
