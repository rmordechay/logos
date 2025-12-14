#include "types/iterables/LgsMap.h"
#include "Lgs_HashMap.h"
#include "LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"

LgsFunc* LgsMap::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto func = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            const auto map = args[0].expr->IRValue;
            const auto key = args[1].expr->IRValue;
            const auto value = args[2].expr->IRValue;
            const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()};
            const std::vector<Value*> IRArgs = {map, getRTType(cg), key, value};
            return cg.callLgsFunc(name, "add", cg.ptrTy(), params, IRArgs);
        };
        addMethod(func);
        return func;
    }
    if (methodName == KEYS_FUNC_NAME) {
        if (methods.contains(KEYS_FUNC_NAME)) return methods[KEYS_FUNC_NAME];
        const auto func = new LgsFunc(KEYS_FUNC_NAME, name, new LgsDArray(mapType->key), {this}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
            const std::vector<Value*> IRArgs = {args[0].expr->IRValue, mapType->key->getRTType(cg)};
            return cg.callLgsFunc(name, "keys", cg.ptrTy(), params, IRArgs);
        };
        addMethod(func);
        return func;
    }
    if (methodName == VALUES_FUNC_NAME) {
        if (methods.contains(VALUES_FUNC_NAME)) return methods[VALUES_FUNC_NAME];
        const auto func = new LgsFunc(VALUES_FUNC_NAME, name, new LgsDArray(mapType->value), {this}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
            const std::vector<Value*> IRArgs = {args[0].expr->IRValue, mapType->value->getRTType(cg)};
            return cg.callLgsFunc(name, "values", cg.ptrTy(), params, IRArgs);
        };
        addMethod(func);
        return func;
    }
    return LgsIterable::getMethod(methodName);
}

Type* LgsMap::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    const std::vector<Type*> mapStructFields = {cg.i64Ty(), cg.i64Ty(), cg.i64Ty(), cg.ptrTy()};
    IRType = cg.getStructType(mapStructFields, name);
    return IRType;
}

Constant* LgsMap::getRTType(LgsCgModule& cg) {
    const auto mapName = getName();
    const auto sv = cg.getRTTExtraStruct(mapName, {cg.ptrTy(), cg.ptrTy()}, {mapType->key->getRTType(cg), mapType->value->getRTType(cg)});
    return cg.getRTTypeInfo(mapName, sizeBytes(), RTT_MAP, isHeapAlloc, sv);
}

std::string LgsMap::getName() {
    return name;
}

std::string LgsMap::pname() {
    const auto keyName = mapType->key ? mapType->key->pname() : LGS_UNKNOWN_TYPE;
    const auto valueName = mapType->value ? mapType->value->pname() : LGS_UNKNOWN_TYPE;
    return '{' + keyName + ": " + valueName + '}';
}

size_t LgsMap::sizeBytes() {
    return sizeof(Lgs_HashMap);
}

LgsExpr* LgsMap::getZeroValue() {
    return new LgsHashMap(this);
}

LgsType* LgsMap::getIndexType() {
    return mapType->key;
}

LgsType* LgsMap::getValueType() {
    return mapType->value;
}

LgsType* LgsMap::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

bool LgsMap::inferBaseType(const std::vector<LgsExpr*>& args) {
    assert(0);
}

bool LgsMap::unpackLoopVarsTypes(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() == 1) {
        loop->loopVars[0]->setType(mapType->key);
        return true;
    }
    if (loop->loopVars.size() == 2) {
        loop->loopVars[0]->setType(mapType->key);
        loop->loopVars[1]->setType(mapType->value);
        return true;
    }
    return false;
}

void LgsMap::unpackLoopIR(LgsCgModule& cg, LgsForeachLoop* loop) const {
    const auto keyPtr = cg.callLgsFunc(name, "getKeyAt", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {loop->iterExpr->IRValue, cg.extendToSize(loop->iValue)});
    loop->loopVars[0]->IRValue = keyPtr;
    if (loop->loopVars.size() == 2) {
        const auto valuePtr = cg.callLgsFunc(name, "getValueAt", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {loop->iterExpr->IRValue, cg.extendToSize(loop->iValue)});
        loop->loopVars[1]->IRValue = valuePtr;
    }
}

Value* LgsMap::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.callLgsFunc(name, "len", cg.sizeTy(), {cg.ptrTy()}, {iterable});
}

Value* LgsMap::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}

Value* LgsMap::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    return cg.callLgsFunc(name, "get", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterable, index});
}

bool LgsMap::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->mapType;
    if (!mapType->key || !mapType->value) return false;
    const auto keyEqual = mapType->key->canCastTo(otherKvType->key);
    return keyEqual && mapType->value->canCastTo(otherKvType->value);
}

std::string LgsMap::fmtStr() const {
    return "%s";
}

DIType* LgsMap::getDebugType(LgsCgModule& cg) {
    assert(0);
}
