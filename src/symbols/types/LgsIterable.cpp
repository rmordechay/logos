#include "types/LgsIterable.h"

#include "exprs/LgsExpr.h"
#include "types/LgsAny.h"

size_t LgsIterable::getDims() const {
    return sizes.size();
}

bool LgsIterable::isIterable() {
    return true;
}

LgsType* LgsIterable::getUnderlyingType() {
    return underlyingType;
}

Value* LgsIterable::IRLength(CodeGenMetadata* metadata) {
    assert(false);
}

LgsType* LgsIterable::inferTypeFromIter(const vector<LgsExpr*>& exprs) const {
    if (exprs.empty()) return nullptr;
    const auto type = exprs[0]->type;
    for (int i = 0; i < exprs.size(); ++i) {
        const auto exprType = exprs[i]->type;
        if (!type->equals(exprType)) {
            return &LGS_ANY;
        }
    }
    return type;
}
