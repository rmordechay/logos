#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/LgsSubType.h"
#include "utils/LgsUtils.h"

LgsExpr* LgsStrConst::staticCast(LgsType* toType, const bool explicitCast) {
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

Value* LgsStrConst::castIR(LgsLLVMGen& cg, LgsType* toType) {
    if (toType->asStr()) return IRValue;
    if (toType->asGeneric()) return IRValue;
    return LgsExpr::castIR(cg, toType);
}

Value* LgsStrConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsStrConst::asText() {
    const auto quote = isSingleQuoted ? '\'' : '\"';
    return quote + scanEscapeStr(value) + quote;
}

Value* LgsStrConst::hashValue(LgsLLVMGen& cg) {
    return cg.hashConst(value);
}

void LgsStrConst::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, value);
}

bool LgsStrConst::equals(LgsExpr* other) {
    const auto otherStrConst = other->asStrConst();
    if (otherStrConst->value == value) return true;
    assert(0);
}

LgsExpr* LgsStrConst::cloneExpr() {
    return new LgsStrConst(*this);
}

void LgsStrConst::setDebugValue(LgsLLVMGen& cg) {
    cg.builder.SetCurrentDebugLocation(getDebugLoc(cg));
}

LgsStrConst::~LgsStrConst() {
    for (const auto part : parts) {
        freeExpr(part);
    }
    parts.clear();
}
