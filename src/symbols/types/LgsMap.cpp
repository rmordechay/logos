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

Value* LgsMap::getLength(LgsModule* runtime, LgsExpr* expr) {
    return lenFunc.call(runtime, {expr});
}

Value* LgsMap::getLoopLength(LgsModule* runtime, LgsExpr* expr) {
    return runtime->builder.getInt32(1024);
}

Value* LgsMap::isEmpty(LgsModule* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsMap::isNotEmpty(LgsModule* runtime, LgsExpr* expr) {
    return isNotEmptyFunc.call(runtime, {expr});
}

Type* LgsMap::getIRType(LLVMContext& context) {
    return ptrTy(context);
}

string LgsMap::getIRName() {
    return name;
}

string LgsMap::prettyName() const {
    return '{' + typePair->key->prettyName() + ": " + typePair->value->prettyName() + '}';
}

bool LgsMap::equals(LgsType* other) {
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->typePair;
    const auto keyEqual = typePair->key->equals(otherKvType->key);
    return keyEqual && typePair->value->equals(otherKvType->value);
}

StructType* LgsMap::getMapStruct(LgsModule* runtime) {
    if (mapStruct) return mapStruct;
    auto& builder = runtime->builder;
    const vector<Type*> mapStructFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt64Ty()};
    mapStruct = getIRStructType(runtime->context, name, mapStructFields);
    return mapStruct;
}
