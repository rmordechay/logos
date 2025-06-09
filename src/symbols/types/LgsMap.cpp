#include "types/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsVarDec.h"

void LgsMap::setBaseType(const vector<LgsMapPair*>& exprs) {
    if (exprs.empty()) return;
    kvType.key = exprs.front()->key->type;
    kvType.value = exprs.front()->value->type;
}

size_t LgsMap::getSizeBytes() {
    return sizeof(void*);
}

void LgsMap::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = kvType.key;
    varDecs[1]->type = kvType.value;
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

StructType* LgsMap::getMapStruct(LgsRuntime* runtime) {
    if (mapStruct) return mapStruct;
    auto& builder = runtime->builder;
    const vector<Type*> mapStructFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt64Ty()};
    mapStruct = getIRStructType(context, name, mapStructFields);
    return mapStruct;
}
