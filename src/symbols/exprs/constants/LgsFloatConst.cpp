#include "exprs/constants/LgsFloatConst.h"

#include "LgsType.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsFloatConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsFloatConst::addIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsFloatConst::subIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFSub(l, r);
}

Value* LgsFloatConst::mulIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFMul(l, r);
}

Value* LgsFloatConst::divIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFDiv(l, r);
}

Value* LgsFloatConst::inIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsFloatConst::modIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFRem(l, r);
}

Value* LgsFloatConst::eqIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFCmpOEQ(l, r);
}

Value* LgsFloatConst::neIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFCmpUNE(l, r);
}

Value* LgsFloatConst::ltIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFCmpOLT(l, r);
}

Value* LgsFloatConst::gtIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFCmpOGT(l, r);
}

Value* LgsFloatConst::geIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFCmpOGE(l, r);
}

Value* LgsFloatConst::leIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateFCmpOLE(l, r);
}

Value* LgsFloatConst::andIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsFloatConst::orIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsFloatConst::bitAndIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsFloatConst::bitOrIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsFloatConst::bitXorIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsFloatConst::rshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsFloatConst::lshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}


json::value LgsFloatConst::asJSON() {
    assert(0);
}

std::string LgsFloatConst::pname() {
    return std::to_string(value);
}
