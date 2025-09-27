#include "exprs/LgsHashMap.h"

void LgsHashMap::completeType(LgsType* toType) {
    if (!toType->asMap()) return;
    if (!type) {
        type = toType;
    }
}

std::string LgsHashMap::getName() {
    return type->pname();
}

json::value LgsHashMap::asJsonStr() {
    assert(0);
}

LgsHashMap::~LgsHashMap() {
    for (const auto initialElement : initialElements) {
        delete initialElement;
    }
    initialElements.clear();
}

LgsMapEntry::~LgsMapEntry() {
    if (key) {
        freeExpr(key);
        key = nullptr;
    }
    if (value) {
        freeExpr(value);
        value = nullptr;
    }
}
