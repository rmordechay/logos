#include "types/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

size_t LgsMap::getSizeBytes() {
    return sizeof(void*);
}

void LgsMap::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    const auto kvType = getTypePair();
    varDecs[0]->type = kvType->key;
    varDecs[1]->type = kvType->value;
}

LgsTypePair* LgsMap::getTypePair() const {
    return baseType->asPair();
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
    return new LgsHashMap(this);
}

string LgsMap::prettyName() const {
    const auto kvType = getTypePair();
    return '{' + kvType->key->prettyName() + ':' + kvType->value->prettyName() + '}';
}

bool LgsMap::equals(LgsType* other) {
    const auto kvType = getTypePair();
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->getTypePair();
    const auto keyEqual = kvType->key->equals(otherKvType->key);
    return keyEqual && kvType->value->equals(otherKvType->value);
}

LgsType* LgsMap::inferBinaryType(LgsType* other) {
    assert(false);
}

StructType* LgsMap::getMapStruct(LgsRuntime* runtime) {
    if (mapStruct) return mapStruct;
    auto& builder = runtime->builder;
    const vector<Type*> mapStructFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt64Ty()};
    mapStruct = getIRStructType(context, name, mapStructFields);
    return mapStruct;
}
