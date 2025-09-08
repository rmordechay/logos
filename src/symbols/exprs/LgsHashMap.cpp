#include "exprs/LgsHashMap.h"

std::string LgsHashMap::pname() {
    return type->pname();
}

json::value LgsHashMap::asJSON() {
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
