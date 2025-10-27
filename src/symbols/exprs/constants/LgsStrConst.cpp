#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/LgsSubType.h"
#include "utils/LgsUtils.h"

LgsExpr* LgsStrConst::castTo(LgsType* toType, const bool explicitCast) {
    const auto thisName = type->getName();
    const auto otherName = toType->getName();
    if (otherName == LgsAny::name) return this;
    if (const auto subtype = toType->asSubtype()) {
        if (explicitCast && subtype->subtype->getName() == thisName) {
            freeType(type);
            type = subtype;
            return this;
        }
    }
    if (thisName == otherName) return this;
    return nullptr;
}

Value* LgsStrConst::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    if (toType->asStr()) return IRValue;
    return LgsExpr::castToIR(cg, toType);
}

Value* LgsStrConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsStrConst::asText() {
    return '"' + value + '"';
}

Value* LgsStrConst::hash(LgsLLVMGen& cg) {
    return cg.usize(hashStr(value.c_str()));
}

LgsStrConst::~LgsStrConst() {
    for (const auto part : parts) {
        freeExpr(part);
    }
    parts.clear();
}

