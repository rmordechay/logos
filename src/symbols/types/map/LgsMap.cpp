#include "types/map/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsVarDec.h"

void LgsMap::setBaseType(const vector<LgsMapPair*>& exprs) {
    vector<LgsExpr*> keyExprs;
    vector<LgsExpr*> valueExprs;
    for (const auto expr : exprs) {
        keyExprs.emplace_back(expr->key);
        valueExprs.emplace_back(expr->value);
    }
    kvType.key = inferTypeFromIter(keyExprs);
    kvType.value = inferTypeFromIter(valueExprs);
}

int LgsMap::getDims() {
    return 1;
}

LgsType* LgsMap::createInnerType(size_t indexRange, LgsIndex* index) const {
    assert(false);
}

void LgsMap::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = kvType.key;
    varDecs[1]->type = kvType.value;
}

Type* LgsMap::getIRType() {
    return ptrTy;
}

string LgsMap::getIRName() {
    return name;
}

LgsExpr* LgsMap::getZeroValue() {
    return new LgsHashMap(kvType.key, kvType.value);
}

string LgsMap::prettyName() const {
    return '{' + kvType.key->prettyName() + ':' + kvType.value->prettyName() + '}';
}

bool LgsMap::equals(LgsType* other) {
    const auto otherMap = other->asMap();
    const auto keyEqual = otherMap && kvType.key->equals(otherMap->kvType.key);
    return keyEqual && kvType.value->equals(otherMap->kvType.value);
}

LgsType* LgsMap::inferBinaryType(LgsType* other) {
    assert(false);
}

bool LgsMap::canIndexTo(LgsType* indexType) {
    return kvType.key->equals(indexType);
}

LgsType* LgsMap::getBaseType() {
    return kvType.value;
}