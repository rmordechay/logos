#include "exprs/constants/LgsStrConst.h"

#include <assert.h>

#include "LgsUtils.h"

std::string LgsStrConst::asText() {
    return '\"' + scanEscapeStr(value) + '\"';
}

void LgsStrConst::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, value);
}

bool LgsStrConst::equals(LgsExpr* other) {
    const auto otherStrConst = other->asStrConst();
    if (otherStrConst->value == value) return true;
    assert(0);
}

void LgsStrConst::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
}

LgsExpr* LgsStrConst::clone() const {
    const auto newStrConst = new LgsStrConst(*this);
    if (!parts.empty()) {
        newStrConst->parts.clear();
        for (const auto part : parts) {
            newStrConst->parts.emplace_back(part->clone());
        }
    }
    return newStrConst;
}

LgsStrConst::~LgsStrConst() {
    for (const auto part : parts) {
        freeExpr(part);
    }
    parts.clear();
}
