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

void LgsMap::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = typePair->key;
    varDecs[1]->type = typePair->value;
}

Value* LgsMap::getLength(LgsRuntime* runtime, LgsExpr* expr) {
    return lenFunc.call(runtime, {expr});
}

Value* LgsMap::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    return runtime->builder.getInt32(1024);
}

Value* LgsMap::callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsMap::callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmptyFunc.call(runtime, {expr});
}

Type* LgsMap::getIRType() {
    return PointerType::getUnqual(context);
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

LgsType* LgsMap::inferBinaryType(LgsType* other) {
    assert(0);
}

StructType* LgsMap::getMapStruct(LgsRuntime* runtime) {
    if (mapStruct) return mapStruct;
    auto& builder = runtime->builder;
    const vector<Type*> mapStructFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt64Ty()};
    mapStruct = getIRStructType(context, name, mapStructFields);
    return mapStruct;
}
