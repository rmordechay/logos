#include "types/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

size_t LgsMap::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsMap::getZeroValue() {
    return new LgsHashMap(this);
}

LgsType* LgsMap::getIndexType() {
    return typePair->key;
}

LgsType* LgsMap::getValueType() {
    return typePair->key;
}

Value* LgsMap::getLength(LgsModule* module, LgsExpr* expr) {
    return lenFunc.call(module, {expr});
}

Value* LgsMap::getLoopLength(LgsModule* module, LgsExpr* expr) {
    return i32(module, 1024);
}

Value* LgsMap::isEmpty(LgsModule* module, LgsExpr* expr) {
    return isEmptyFunc.call(module, {expr});
}

Value* LgsMap::isNotEmpty(LgsModule* module, LgsExpr* expr) {
    return isNotEmptyFunc.call(module, {expr});
}

Type* LgsMap::getIRType(LgsModule* module) {
    return getMapStruct(module);
}

string LgsMap::getName() {
    return name;
}

string LgsMap::prettyName() {
    return '{' + typePair->key->prettyName() + ": " + typePair->value->prettyName() + '}';
}

bool LgsMap::equals(LgsType* other) {
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->typePair;
    const auto keyEqual = typePair->key->equals(otherKvType->key);
    return keyEqual && typePair->value->equals(otherKvType->value);
}

StructType* LgsMap::getMapStruct(LgsModule* module) {
    if (mapStruct) return mapStruct;
    const vector<Type*> mapStructFields = {ptrTy(module), i64Ty(module), i64Ty(module)};
    mapStruct = getIRStructType(module->context, name, mapStructFields);
    return mapStruct;
}
