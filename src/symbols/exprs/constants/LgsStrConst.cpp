#include "exprs/constants/LgsStrConst.h"

LgsExpr* LgsStrConst::castTo(LgsType* toType, bool explicitCast) {
    return LgsExpr::castTo(toType, explicitCast);
}

Value* LgsStrConst::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    return LgsExpr::castToIR(cg, toType);
}

Value* LgsStrConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsStrConst::asText() {
    return '"' + value + '"';
}

Value* LgsStrConst::hash(LgsLLVMGen& cg) {
    return cg.i32(hashStr(value.c_str()));
}

LgsStrConst::~LgsStrConst() {
    for (const auto part : parts) {
        freeExpr(part);
    }
    parts.clear();
}

