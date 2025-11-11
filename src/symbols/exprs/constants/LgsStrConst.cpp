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
            setType(subtype);
            return this;
        }
    }
    if (thisName == otherName) return this;
    return nullptr;
}

Value* LgsStrConst::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    if (toType->asStr()) return IRValue;
    if (toType->asGeneric()) return IRValue;
    return LgsExpr::castToIR(cg, toType);
}

Value* LgsStrConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsStrConst::asText() {
    const auto quote = isSingleQuoted ? '\'' : '\"';
    return quote + scanEscapeStr(value) + quote;
}

Value* LgsStrConst::hash(LgsLLVMGen& cg) {
    const auto hashed = std::hash<std::string_view>{}(value.c_str());
    return cg.usize(hashed);
}

void LgsStrConst::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, value);
}

LgsExpr* LgsStrConst::cloneExpr() {
    return new LgsStrConst(*this);
}

LgsStrConst::~LgsStrConst() {
    for (const auto part : parts) {
        freeExpr(part);
    }
    parts.clear();
}
