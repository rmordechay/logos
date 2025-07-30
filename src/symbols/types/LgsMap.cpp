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

Value* LgsMap::getLength(LgsCodeGen* codeGen, LgsExpr* expr) {
    return lenFunc.call(codeGen, {expr});
}

Value* LgsMap::getLoopLength(LgsCodeGen* codeGen, LgsExpr* expr) {
    return codeGen->i32(1024);
}

Value* LgsMap::isEmpty(LgsCodeGen* codeGen, LgsExpr* expr) {
    return isEmptyFunc.call(codeGen, {expr});
}

Value* LgsMap::isNotEmpty(LgsCodeGen* codeGen, LgsExpr* expr) {
    return isNotEmptyFunc.call(codeGen, {expr});
}

Type* LgsMap::getIRType(LgsCodeGen* codeGen) {
    return getMapStruct(codeGen);
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

void LgsMap::freeValue(LgsCodeGen* codeGen, Value* value) {
    freeFunc.callIR(codeGen, {value});
}

StructType* LgsMap::getMapStruct(LgsCodeGen* codeGen) {
    if (mapStruct) return mapStruct;
    const vector<Type*> mapStructFields = {codeGen->ptrTy(), codeGen->i64Ty(), codeGen->i64Ty()};
    mapStruct = codeGen->getIRStructType(name, mapStructFields);
    return mapStruct;
}
