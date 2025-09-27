#include "types/iterables/LgsMap.h"

#include "data/LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsVoid.h"

Type* LgsMap::getIRType(LgsLLVMGen& cg) {
    return getMapStruct(cg);
}

std::string LgsMap::getName() {
    return name;
}

std::string LgsMap::pname() {
    return '{' + (typePair->key ? typePair->key->pname() : LGS_UNKNOWN_TYPE) + ": " + (typePair->value ? typePair->value->pname() : LGS_UNKNOWN_TYPE) + '}';
}

json::value LgsMap::asJSON() {
    assert(0);
}

LgsFunc* LgsMap::getAddFunc() {
    const auto addFunc = methods.find(ADD_FUNC_NAME);
    if (addFunc != methods.end() && addFunc->second) return addFunc->second;
    addFunc->second = new LgsFunc(ADD_FUNC_NAME, &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, PUBLIC | BUILTIN | METHOD);
    addFunc->second->fn = [addFunc](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        const auto key = args[1];
        const auto value = args[2];
        const auto mapPtr = args[0]->IRValue;
        if (value->type->asDArray()) {
            return addFunc->second->callIR(cg, {mapPtr, key->IRValue, value->IRValue});
        }
        const auto valurPtr = cg.builder.CreateAlloca(value->type->getIRType(cg));
        cg.builder.CreateStore(value->IRValue, valurPtr);
        return addFunc->second->callIR(cg, {mapPtr, key->IRValue, valurPtr});
    };
    addMethod(addFunc->second);
    return addFunc->second;
}

size_t LgsMap::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsMap::getZeroValue() {
    return new LgsHashMap(this);
}

Lgs_RTType LgsMap::getRTType() {
    return RTT_MAP;
}

LgsType* LgsMap::getIndexType() {
    return typePair->key;
}

uint16_t LgsMap::getUnpackCount() const {
    return 2;
}

Value* LgsMap::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return cg.i32(1024);
}

Value* LgsMap::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}

Value* LgsMap::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    LgsFunc f("get", &LGS_ANY, {this, new LgsStr()}, PUBLIC | BUILTIN | METHOD);
    return f.callIR(cg, {iterable, index});
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
    if (!typePair->key || !typePair->value) return false;
    const auto keyEqual = typePair->key->canCastTo(otherKvType->key);
    return keyEqual && typePair->value->canCastTo(otherKvType->value);
}

std::string LgsMap::strFormatPart() const {
    return "%s";
}

LgsMap::~LgsMap() {
    freeType(typePair);
    typePair = nullptr;
}
