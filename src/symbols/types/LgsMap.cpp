#include "types/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsVarDec.h"

Value* LgsMapAddFunc::call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) {
    const auto arr = args[0];
    const auto keyIR = args[1]->getIRValue(codeGen);
    const auto value = args[2];
    const auto exprIR = value->getIRValue(codeGen);
    const auto arrPtr = arr->getIRValue(codeGen);
    const auto exprTy = value->type;
    const auto ptr = codeGen->builder.CreateAlloca(exprTy->getIRType(codeGen));
    codeGen->builder.CreateStore(exprIR, ptr);
    return callIR(codeGen, {arrPtr, keyIR, ptr});
}

Type* LgsMap::getIRType(LgsCodeGen* codeGen) {
    return getMapStruct(codeGen);
}

std::string LgsMap::getName() {
    return name;
}

std::string LgsMap::pname() {
    return '{' + typePair->key->pname() + ": " + typePair->value->pname() + '}';
}

json::value LgsMap::asJSON() {
    assert(0);
}

size_t LgsMap::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsMap::getZeroValue() {
    return new LgsHashMap(this);
}

LgsType* LgsMap::getIndexType() {
    return typePair->key;
}

uint16_t LgsMap::getUnpackCount() const {
    return 2;
}

Value* LgsMap::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->i32(1024);
}

Value* LgsMap::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isEmptyFunc->call(codeGen, {iterable});
}

Value* LgsMap::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc->call(codeGen, {iterable});
}

StructType* LgsMap::getMapStruct(LgsCodeGen* codeGen) {
    const std::vector<Type*> mapStructFields = {codeGen->ptrTy(), codeGen->i64Ty(), codeGen->i64Ty()};
    mapStruct = codeGen->getStructType(mapStructFields, name);
    return mapStruct;
}

bool LgsMap::equals(LgsType* other) {
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->typePair;
    const auto keyEqual = typePair->key->equals(otherKvType->key);
    return keyEqual && typePair->value->equals(otherKvType->value);
}

void LgsMap::freeValue(LgsCodeGen* codeGen, Value* value) {
    freeFunc->callIR(codeGen, {value});
}

std::string LgsMap::strFormatPart() const {
    return "%s";
}

LgsMap::~LgsMap() {
    freeType(typePair);
    delete addFunc;
    delete initFunc;
    delete getFunc;
    delete deleteFunc;
    delete freeFunc;
    typePair = nullptr;
    addFunc = nullptr;
    initFunc = nullptr;
    getFunc = nullptr;
    deleteFunc = nullptr;
    freeFunc = nullptr;
}
