#include "exprs/LgsHashMap.h"

#include "utils/LgsUtils.h"

void LgsHashMap::completeType(LgsType* toType) {
    if (!toType->asMap()) return;
    if (!type) {
        setType(toType);
    }
}

bool LgsHashMap::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsHashMap::asText() {
    return type->pname();
}

LgsHashMap::~LgsHashMap() {
    for (const auto initialElement : pairs) {
        freeExpr(initialElement.key);
        freeExpr(initialElement.value);
    }
    pairs.clear();
}

