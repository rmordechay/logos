#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

Value* LgsIntConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::castTo(LgsType* toType) {
    if (type->getName() == toType->getName()) return this;
    if (toType->asLong()) {
        return new LgsIntConst(&LGS_LONG, value);
    }
    if (toType->asFloat()) {
        return new LgsFloatConst(&LGS_FLOAT, value);
    }
    if (toType->asDouble()) {
        return new LgsFloatConst(&LGS_DOUBLE, value);
    }
    assert(0);
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(*this);
}

std::string LgsIntConst::pname() {
    return std::to_string(value);
}

Value* LgsIntConst::addIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateAdd(l, r);
}

Value* LgsIntConst::subIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateSub(l, r);
}

Value* LgsIntConst::mulIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateMul(l, r);
}

Value* LgsIntConst::divIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateSDiv(l, r);
}

Value* LgsIntConst::inIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsIntConst::modIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateSRem(l, r);
}

Value* LgsIntConst::eqIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateICmpEQ(l, r);
}

Value* LgsIntConst::neIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateICmpNE(l, r);
}

Value* LgsIntConst::ltIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateICmpSLT(l, r);
}

Value* LgsIntConst::gtIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateICmpSGT(l, r);
}

Value* LgsIntConst::geIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateICmpSGE(l, r);
}

Value* LgsIntConst::leIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateICmpSLE(l, r);
}

Value* LgsIntConst::andIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsIntConst::orIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

Value* LgsIntConst::bitAndIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateAnd(l, r);
}

Value* LgsIntConst::bitOrIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateOr(l, r);
}

Value* LgsIntConst::bitXorIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateXor(l, r);
}

Value* LgsIntConst::lshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateShl(l, r);
}

Value* LgsIntConst::rshiftIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto l = loadIR(cg);
    const auto r = other->loadIR(cg);
    return cg.builder.CreateLShr(l, r);
}

json::value LgsIntConst::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "intConst";
    jsonObj["name"] = pname();
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}
