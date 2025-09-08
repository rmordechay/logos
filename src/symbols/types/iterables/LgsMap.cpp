#include "types/iterables/LgsMap.h"
#include "exprs/LgsHashMap.h"
#include "stmts/LgsVarDec.h"

Type* LgsMap::getIRType(LgsLLVMGen& cg) {
    return getMapStruct(cg);
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

Value* LgsMap::IRLength(LgsLLVMGen& cg, LgsExpr* iterable) {
    return cg.i32(1024);
}

Value* LgsMap::IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return isEmptyFunc->call(*cg, {iterable});
}

Value* LgsMap::IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return isNotEmptyFunc->call(*cg, {iterable});
}

StructType* LgsMap::getMapStruct(LgsLLVMGen& cg) {
    const std::vector<Type*> mapStructFields = {cg.ptrTy(), cg.i64Ty(), cg.i64Ty()};
    mapStruct = cg.getStructType(mapStructFields, name);
    return mapStruct;
}

bool LgsMap::canCastTo(LgsType* other) {
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->typePair;
    const auto keyEqual = typePair->key->canCastTo(otherKvType->key);
    return keyEqual && typePair->value->canCastTo(otherKvType->value);
}

void LgsMap::freeValue(LgsLLVMGen& cg, LgsExpr* value) {
    freeFunc->callIR(cg, {value->IRValue});
}

std::string LgsMap::strFormatPart() const {
    return "%s";
}

Value* LgsMap::callAdd(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) const {
    const auto map = args[0];
    const auto key = args[1];
    const auto value = args[2];
    const auto exprIR = value->IRValue;
    const auto mapPtr = map->IRValue;
    const auto exprTy = value->type;
    if (exprTy->asDArray()) {
        return addFunc->callIR(cg, {mapPtr, key->IRValue, value->IRValue});
    }
    const auto valurPtr = cg.builder.CreateAlloca(exprTy->getIRType(cg));
    cg.builder.CreateStore(exprIR, valurPtr);
    return addFunc->callIR(cg, {mapPtr, key->IRValue, valurPtr});
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
