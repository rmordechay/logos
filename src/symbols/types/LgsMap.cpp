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

Value* LgsMap::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->i32(1024);
}

Value* LgsMap::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isEmptyFunc.call(codeGen, {iterable});
}

Value* LgsMap::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc.call(codeGen, {iterable});
}

Type* LgsMap::getIRType(LgsCodeGen* codeGen) {
    return getMapStruct(codeGen);
}

std::string LgsMap::getName() {
    return name;
}

std::string LgsMap::prettyName() {
    return '{' + typePair->key->prettyName() + ": " + typePair->value->prettyName() + '}';
}

bool LgsMap::equals(LgsType* other) {
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->typePair;
    const auto keyEqual = typePair->key->equals(otherKvType->key);
    return keyEqual && typePair->value->equals(otherKvType->value);
}

void LgsMap::freeValue(LgsCodeGen* codeGen, Value* value) {
    freeFunc.callIR(codeGen, {value});
}

StructType* LgsMap::getMapStruct(LgsCodeGen* codeGen) {
    const std::vector<Type*> mapStructFields = {codeGen->ptrTy(), codeGen->i64Ty(), codeGen->i64Ty()};
    mapStruct = codeGen->getStructType(mapStructFields, name);
    return mapStruct;
}
