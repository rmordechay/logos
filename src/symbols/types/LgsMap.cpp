#include "types/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"

Type* LgsMap::getIRType() {
    return ptrTy;
}

string LgsMap::getIRName() {
    return name;
}

LgsExpr* LgsMap::getZeroValue() {
    const auto hashMap = new LgsHashMap();
    hashMap->mapType.underlyingType.key = underlyingType.key;
    hashMap->mapType.underlyingType.value = underlyingType.value;
    hashMap->mapType.sizes.emplace_back(1);
    return hashMap;
}

string LgsMap::prettyName() const {
    return name  + underlyingType.prettyName();
}

bool LgsMap::equals(LgsType* other) const {
    assert(false);
}

LgsType* LgsMap::inferBinaryType(LgsType* other) {
    assert(false);
}

bool LgsMap::isIndexable(LgsType* indexType) {
    return underlyingType.key->equals(indexType);
}

LgsType* LgsMap::getUnderlyingType() {
    return underlyingType.value;
}
