#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/LgsSubType.h"
#include "LgsUtils.h"

LgsExpr* LgsStrConst::castExplicitly(LgsType* toType) {
    const auto thisName = type->getName();
    const auto otherName = toType->getName();
    if (otherName == LgsAny::name) return this;
    if (const auto subtype = toType->asSubtype()) {
        if (subtype->subtype->getName() == thisName) {
            freeType(type);
            setType(subtype);
            return this;
        }
    }
    if (thisName == otherName) return this;
    return nullptr;
}

Value* LgsStrConst::loadIR(LgsCgModule& cg) {
    return IRValue;
}

std::string LgsStrConst::asText() {
    const auto quote = isSingleQuoted ? '\'' : '\"';
    return quote + scanEscapeStr(value) + quote;
}

Value* LgsStrConst::hashValue(LgsCgModule& cg) {
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

void LgsStrConst::setDebugValue(LgsCgModule& cg) {
    setDebugLoc(cg);
}

LgsStrConst::~LgsStrConst() {
    for (const auto part : parts) {
        freeExpr(part);
    }
    parts.clear();
}
