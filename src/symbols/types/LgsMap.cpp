#include "types/LgsMap.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsVarDec.h"

Value* LgsMap::callAdd(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) const {
    const auto map = args[0];
    const auto key = args[1];
    const auto value = args[2];
    const auto exprIR = value->IRValue;
    const auto mapPtr = map->IRValue;
    const auto exprTy = value->type;
    const auto valurPtr = codeGen.builder.CreateAlloca(exprTy->getIRType(codeGen));
    codeGen.builder.CreateStore(exprIR, valurPtr);
    return addFunc->callIR(codeGen, {mapPtr, key->IRValue, valurPtr});
}

Type* LgsMap::getIRType(LgsLLVM& codeGen) {
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

Value* LgsMap::IRLength(LgsLLVM& codeGen, LgsExpr* iterable) {
    return codeGen.i32(1024);
}

Value* LgsMap::IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return isEmptyFunc->call(*codeGen, {iterable});
}

Value* LgsMap::IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc->call(*codeGen, {iterable});
}

StructType* LgsMap::getMapStruct(LgsLLVM& codeGen) {
    const std::vector<Type*> mapStructFields = {codeGen.ptrTy(), codeGen.i64Ty(), codeGen.i64Ty()};
    mapStruct = codeGen.getStructType(mapStructFields, name);
    return mapStruct;
}

bool LgsMap::canCastTo(LgsType* other) {
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->typePair;
    const auto keyEqual = typePair->key->canCastTo(otherKvType->key);
    return keyEqual && typePair->value->canCastTo(otherKvType->value);
}

void LgsMap::freeValue(LgsLLVM& codeGen, Value* value) {
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
