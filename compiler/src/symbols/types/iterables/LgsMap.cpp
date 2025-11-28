#include "types/iterables/LgsMap.h"
#include "Lgs_HashMap.h"
#include "LgsDefinitions.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsIterIndex.h"
#include "funcs/LgsFunc.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"
#include "types/iterables/LgsDArray.h"
#include "LgsUtils.h"

Type* LgsMap::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    const std::vector<Type*> mapStructFields = {cg.i64Ty(), cg.i64Ty(), cg.i64Ty(), cg.ptrTy()};
    IRType = cg.getStructType(mapStructFields, name);
    return IRType;
}

Constant* LgsMap::getRTType(LgsCgModule& cg) {
    const auto genericName = getGenericName();
    const auto st = cg.getStructType({cg.ptrTy(), cg.ptrTy()}, genericName);
    const auto sv = llvm::ConstantStruct::get(st, {mapType->key->getRTType(cg), mapType->value->getRTType(cg)});
    return cg.getRTTypeInfo(genericName, sizeBytes(), RTT_MAP, sv);
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
    const auto keyPtr = cg.callLgsFunc("Map_getKeyAt", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {loop->iterExpr->IRValue, loop->iValue});
    loop->loopVars[0]->IRValue = keyPtr;
    if (loop->loopVars.size() == 2) {
        const auto valuePtr = cg.callLgsFunc("Map_getValueAt", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {loop->iterExpr->IRValue, loop->iValue});
        loop->loopVars[1]->IRValue = valuePtr;
    }
}

Value* LgsMap::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.callLgsFunc("Map_len", cg.sizeTy(), {cg.ptrTy()}, {iterable});
}

Value* LgsMap::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}

Value* LgsMap::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    return cg.callLgsFunc("Map_get", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterable, index});
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

std::string LgsMap::strFormatPart() const {
    return "%s";
}

llvm::DIType* LgsMap::getDebugType(LgsCgModule& cg) {
    assert(0);
}