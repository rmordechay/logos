#include "types/LgsMap.h"

#include "exprs/unary/LgsHashMap.h"

Type* LgsMap::getIRType() {
    assert(false);
}

LgsExpr* LgsMap::getZeroValue() {
    const auto hashMap = new LgsHashMap();
    hashMap->mapType.types.key = types.key;
    hashMap->mapType.types.value = types.value;
    return hashMap;
}

const string LgsMap::getName() const {
    return name;
}

bool LgsMap::equals(LgsType* other) const {
    assert(false);
}

LgsType* LgsMap::inferBinaryType(LgsType* other) {
    assert(false);
}
