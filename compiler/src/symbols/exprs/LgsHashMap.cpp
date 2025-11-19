#include "exprs/LgsHashMap.h"

#include "LgsUtils.h"

void LgsHashMap::castImplicitly(LgsType* toType) {
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
    for (const auto initialElement : elements) {
        freeExpr(initialElement.key);
        freeExpr(initialElement.value);
    }
    elements.clear();
}

