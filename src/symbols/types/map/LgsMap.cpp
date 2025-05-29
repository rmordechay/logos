#include "types/map/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsVarDec.h"

void LgsMap::setBaseType(const vector<LgsMapPair*>& exprs) {
    kvType.key = exprs.front()->key->type;
    kvType.value = exprs.front()->value->type;
}

void LgsMap::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = kvType.key;
    varDecs[1]->type = kvType.value;
}

Value* LgsMap::getLength(CodeGenMetadata* metadata, Value* iterValue) {
    return len.callIR(metadata);
}

Value* LgsMap::getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* iPtr) {
    assert(false);
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

LgsType* LgsMap::getBaseType() {
    return kvType.value;
}