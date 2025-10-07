#include "types/iterables/LgsMap.h"
#include "Lgs_hashmap.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsVoid.h"
#include "types/iterables/LgsDArray.h"

Type* LgsMap::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    const std::vector<Type*> mapStructFields = {cg.i64Ty(), cg.i64Ty(), cg.i64Ty(), cg.ptrTy()};
    IRType = cg.getStructType(mapStructFields, name);
    return IRType;
}

std::string LgsMap::getName() {
    return name;
}

std::string LgsMap::pname() {
    return '{' + (typePair->key ? typePair->key->pname() : LGS_UNKNOWN_TYPE) + ": " + (typePair->value ? typePair->value->pname() : LGS_UNKNOWN_TYPE) + '}';
}

size_t LgsMap::getSizeBytes() {
    return sizeof(Lgs_hashmap);
}

LgsExpr* LgsMap::getZeroValue() {
    return new LgsHashMap(this);
}

Lgs_rttype LgsMap::getRTType() {
    return RTT_MAP;
}

LgsType* LgsMap::getIndexType() {
    return typePair->key;
}

LgsType* LgsMap::getValueType() {
    return typePair->value;
}

bool LgsMap::unpackLoopVarsTypes(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() == 1) {
        loop->loopVars[0]->type = typePair->key;
        return true;
    }
    if (loop->loopVars.size() == 2) {
        loop->loopVars[0]->type = typePair->key;
        loop->loopVars[1]->type = typePair->value;
        return true;
    }
    return false;
}

void LgsMap::unpackLoopIR(LgsLLVMGen& cg, LgsForeachLoop* loop) const {
    const auto keyPtr = cg.callLgsFunc("Map_getKeyAt", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {loop->iterExpr->IRValue, loop->iValue});
    loop->loopVars[0]->IRValue = keyPtr;
    if (loop->loopVars.size() == 2) {
        const auto valuePtr = cg.callLgsFunc("Map_getValueAt", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {loop->iterExpr->IRValue, loop->iValue});
        loop->loopVars[1]->IRValue = valuePtr;
    }
}

Value* LgsMap::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return getLenFunc()->callIR(cg, {iterable});
}

Value* LgsMap::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}

Value* LgsMap::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    LgsFunc f("get", &LGS_ANY, {this, new LgsStr()}, PUBLIC | BUILTIN | METHOD);
    return f.callIR(cg, {iterable, index});
}

LgsFunc* LgsMap::getKeysFunc() {
    const auto func = methods.find(KEYS_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(KEYS_FUNC_NAME, new LgsDArray(typePair->key), {this}, BUILTIN | PUBLIC | METHOD);
    methods[KEYS_FUNC_NAME] = func->second;
    return func->second;
}

LgsFunc* LgsMap::getValuesFunc() {
    const auto func = methods.find(VALUES_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(VALUES_FUNC_NAME, new LgsDArray(typePair->value), {this}, BUILTIN | PUBLIC | METHOD);
    methods[VALUES_FUNC_NAME] = func->second;
    return func->second;
}

LgsFunc* LgsMap::getAddFunc() {
    const auto func = methods.find(ADD_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(ADD_FUNC_NAME, &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, PUBLIC | BUILTIN | METHOD);
    func->second->fn = [func](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        const auto key = args[1];
        const auto value = args[2];
        const auto mapPtr = args[0]->IRValue;
        if (value->type->asDArray()) {
            return func->second->callIR(cg, {mapPtr, key->IRValue, value->IRValue});
        }
        const auto valurPtr = cg.builder.CreateAlloca(value->type->getIRType(cg));
        cg.builder.CreateStore(value->IRValue, valurPtr);
        return func->second->callIR(cg, {mapPtr, key->IRValue, valurPtr});
    };
    methods[ADD_FUNC_NAME] = func->second;
    return func->second;
}

bool LgsMap::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
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
