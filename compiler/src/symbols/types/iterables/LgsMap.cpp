#include "types/iterables/LgsMap.h"
#include "LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"

#include <llvm/IR/Module.h>

#define INITIAL_CAPACITY 3

LgsFunc* LgsMap::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto func = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            addIRElement(cg, args[0].expr, args[1].expr, args[2].expr);
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    if (methodName == KEYS_FUNC_NAME) {
        if (methods.contains(KEYS_FUNC_NAME)) return methods[KEYS_FUNC_NAME];
        const auto func = new LgsFunc(KEYS_FUNC_NAME, name, new LgsDArray(pairType->key), {this}, flags);
        func->fn = [](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    if (methodName == VALUES_FUNC_NAME) {
        if (methods.contains(VALUES_FUNC_NAME)) return methods[VALUES_FUNC_NAME];
        const auto func = new LgsFunc(VALUES_FUNC_NAME, name, new LgsDArray(pairType->value), {this}, flags);
        func->fn = [](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    return LgsIterable::getMethod(methodName);
}

Type* LgsMap::getIRType(LgsCgModule& cg) {
    return cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy()}, name);
}

Constant* LgsMap::getRTType(LgsCgModule& cg) {
    const auto mapName = getName();
    const auto args = {pairType->key->getRTType(cg), pairType->value->getRTType(cg)};
    const auto sv = cg.getRTTExtraStruct(mapName, {cg.ptrTy(), cg.ptrTy()}, args);
    return cg.getRTTypeInfo(mapName, sizeBytes(), RTT_MAP, sv);
}

std::string LgsMap::getBaseName() {
    return name;
}

std::string LgsMap::getName() {
    return name + pairType->key->getName() + pairType->value->getName();
}

std::string LgsMap::pname() {
    const auto keyName = pairType->key ? pairType->key->pname() : LGS_UNKNOWN_TYPE;
    const auto valueName = pairType->value ? pairType->value->pname() : LGS_UNKNOWN_TYPE;
    return '{' + keyName + ": " + valueName + '}';
}

size_t LgsMap::sizeBytes() {
    // entries, len, cap
    return sizeof(void*) + sizeof(size_t) + sizeof(size_t);
}

LgsType* LgsMap::getIndexType() {
    return pairType->key;
}

LgsType* LgsMap::getValueType() {
    return pairType->value;
}

bool LgsMap::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherMap = other->asMap();
    if (!otherMap) return false;
    const auto otherKvType = otherMap->pairType;
    if (!pairType->key || !pairType->value) return false;
    const auto keyEqual = pairType->key->canCastTo(otherKvType->key);
    return keyEqual && pairType->value->canCastTo(otherKvType->value);
}

LgsExpr* LgsMap::getZeroValue() {
    return new LgsHashMap(this);
}

Value* LgsMap::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    const auto ty = getIRType(cg);
    const auto ptr = pointee ? pointee : cg.heapAlloc(cg.usize(sizeBytes()));
    const auto cap = cg.usize(INITIAL_CAPACITY);
    const auto entriesSize = cg.usize(pairType->sizeBytes() + sizeof(void*));
    const auto totalSize = cg.builder.CreateMul(entriesSize, cap);
    const auto entries = cg.heapAlloc(totalSize);
    cg.storeStructField(ty, ptr, 0, entries);
    cg.storeStructField(ty, ptr, 1, cg.sizeZero());
    cg.storeStructField(ty, ptr, 2, cap);
    return ptr;
}

LgsType* LgsMap::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

bool LgsMap::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsMap::loadEntriesField(LgsCgModule& cg, Value* map) {
    return cg.loadStructField(getIRType(cg), map, 0, cg.ptrTy());
}

Value* LgsMap::loadCapField(LgsCgModule& cg, Value* map) {
    return cg.loadStructField(getIRType(cg), map, 2, cg.sizeTy());
}

Value* LgsMap::getEntryKey(LgsCgModule& cg, Value* entry) const {
    return cg.builder.CreateStructGEP(getEntryStruct(cg), entry, 0);
}

Value* LgsMap::getEntryValue(LgsCgModule& cg, Value* entry) const {
    return cg.builder.CreateStructGEP(getEntryStruct(cg), entry, 1);
}

Value* LgsMap::getEntryNext(LgsCgModule& cg, Value* entry) const {
    return cg.builder.CreateStructGEP(getEntryStruct(cg), entry, 2);
}

Value* LgsMap::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.loadStructField(getIRType(cg), iterable, 1, cg.sizeTy());
}

Value* LgsMap::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}

Value* LgsMap::getIRElement(LgsCgModule& cg, LgsExpr* map, LgsExpr* index) {
    const auto cap = loadCapField(cg, map->IRValue);
    const auto hash = cg.builder.CreateURem(index->hashValue(cg), cap);
    const auto entries = loadEntriesField(cg, map->IRValue);
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {hash});
    const auto entry = cg.load(cg.ptrTy(), entryPtr);
    const auto entryValue = getEntryValue(cg, entry);
    if (pairType->value->passByRef) {
        return cg.load(cg.ptrTy(), entryValue);
    }
    return entryValue;
}

void LgsMap::addIRElement(LgsCgModule& cg, LgsExpr* map, LgsExpr* index, LgsExpr* value) {
    const auto funcName = getName() + "_" + ADD_FUNC;
    if (const auto f = cg.IRModule->getFunction(funcName)) {
        cg.builder.CreateCall(f, {map->IRValue, index->IRValue, value->IRValue});
        return;
    }
    const auto mapTy = getIRType(cg);
    const auto valueTy = pairType->value->passByRef ? cg.ptrTy() : pairType->value->getIRType(cg);
    const auto keyType = pairType->key->passByRef ? cg.ptrTy() : pairType->key->getIRType(cg);
    const std::vector<Type*> params = {cg.ptrTy(), keyType, valueTy};
    const auto ft = cg.getFT(cg.voidTy(), params);
    const auto func = cg.getFunc(funcName, ft);

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;
    cg.currentFunc = func;

    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    const auto isNotNullBlock = cg.createBlock("is_not_null");
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);
    cg.builder.SetInsertPoint(entryBlock);

    const auto mapIR = cg.currentFunc->getArg(0);
    const auto keyIR = cg.currentFunc->getArg(1);
    const auto valueIR = cg.currentFunc->getArg(2);

    const auto indexTemp = index->type->getZeroValue();
    const auto entriesField = cg.builder.CreateStructGEP(mapTy, mapIR, 0);
    const auto lenField = cg.builder.CreateStructGEP(mapTy, mapIR, 1);
    const auto capField = cg.builder.CreateStructGEP(mapTy, mapIR, 2);

    // Resize
    auto len = cg.load(cg.sizeTy(), lenField);
    auto cap = cg.load(cg.sizeTy(), capField);
    const auto cond = cg.builder.CreateICmpUGE(len, cap);
    const auto needsResizeBlock = cg.createBlock("resize");
    const auto noResizeBlock = cg.createBlock("store_element");
    const auto condBlock = cg.createBlock("cond");

    cg.builder.CreateCondBr(cond, needsResizeBlock, noResizeBlock);
    cg.startBlock(needsResizeBlock);
    const auto entriesSize = cg.usize(pairType->sizeBytes() + sizeof(void*));
    const auto newCap = cg.builder.CreateMul(entriesSize, cg.builder.CreateMul(cap, cg.usize(2)));
    const auto newEntries = cg.heapAlloc(newCap);
    auto entries = cg.load(cg.ptrTy(), entriesField);

    cg.loop(cap, [&](Value* iValue, BasicBlock*) {
        auto entry = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {iValue});
        entry = cg.load(cg.ptrTy(), entry);
        indexTemp->IRValue = cg.load(pairType->key->getIRType(cg), entry);
        const auto hash = cg.builder.CreateURem(indexTemp->hashValue(cg), newCap);
        const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), newEntries, {hash});
        cg.store(entry, entryPtr);
    });

    // cg.freeValue(entries);
    cg.store(newEntries, entriesField);
    cg.store(newCap, capField);
    cg.branchAndStartBlock(noResizeBlock);

    // Check slot
    indexTemp->IRValue = keyIR;
    cap = cg.load(cg.sizeTy(), capField);
    entries = cg.load(cg.ptrTy(), entriesField);
    const auto hash = cg.builder.CreateURem(indexTemp->hashValue(cg), cap);
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {hash});
    const auto entry = cg.load(cg.ptrTy(), entryPtr);
    const auto v = cg.allocaAndStore(cg.ptrTy(), entry);

    cg.branchAndStartBlock(condBlock);
    auto vLoad = cg.load(cg.ptrTy(), v);
    const auto isNotNull = cg.builder.CreateIsNotNull(vLoad);
    cg.builder.CreateCondBr(isNotNull, isNotNullBlock, exitBlock);

    // Element with same hash
    cg.startBlock(isNotNullBlock);
    vLoad = cg.load(cg.ptrTy(), v);
    const auto next = getEntryNext(cg, vLoad);
    cg.store(cg.load(cg.ptrTy(), next), v);
    cg.builder.CreateBr(condBlock);

    // Store entry
    cg.startBlock(exitBlock);
    const auto entryTy = getEntryStruct(cg);
    const auto newEntry = cg.heapAlloc(cg.usize(pairType->sizeBytes() + sizeof(void*)));
    cg.storeStructField(entryTy, newEntry, 0, keyIR);
    cg.storeStructField(entryTy, newEntry, 1, valueIR);
    cg.storeStructField(entryTy, newEntry, 2, cg.null());
    cg.store(newEntry, entryPtr);

    // Increment length
    len = cg.load(cg.sizeTy(), lenField);
    const auto inc = cg.builder.CreateAdd(len, cg.usize(1));
    cg.store(inc, lenField);

    // Epilogue
    cg.builder.CreateRetVoid();
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);

    // Call
    cg.builder.CreateCall(func, {map->IRValue, index->IRValue, value->IRValue});
    freeExpr(indexTemp);
}

Value* LgsMap::getNewEntry(LgsCgModule& cg, Value* entryPtr, Value* key, Value* value) const {
    const auto entryTy = getEntryStruct(cg);
    const auto entry = cg.heapAlloc(cg.usize(pairType->sizeBytes() + sizeof(void*)));
    cg.storeStructField(entryTy, entry, 0, key);
    cg.storeStructField(entryTy, entry, 1, value);
    cg.storeStructField(entryTy, entry, 2, cg.null());
    cg.store(entry, entryPtr);
    return entry;
}

StructType* LgsMap::getEntryStruct(LgsCgModule& cg) const {
    const auto keyTy = pairType->key->getIRType(cg);
    const auto valueTy = pairType->value->getIRType(cg);
    return cg.getStructType({keyTy, valueTy, cg.ptrTy()}, pairType->getName());
}

bool LgsMap::unpackLoopVarsTypes(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() == 1) {
        loop->loopVars[0]->setType(pairType->key);
        return true;
    }
    if (loop->loopVars.size() == 2) {
        loop->loopVars[0]->setType(pairType->key);
        loop->loopVars[1]->setType(pairType->value);
        return true;
    }
    return false;
}

void LgsMap::unpackLoopIR(LgsCgModule& cg, LgsForeachLoop* loop) {
    const auto map = loop->iterExpr->IRValue;
    const auto foundBlock = cg.createBlock();
    const auto exitBlock = cg.createBlock();

    const auto entries = loadEntriesField(cg, map);
    const auto entry = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {loop->loadIndex(cg)});
    const auto found = cg.builder.CreateIsNull(cg.load(cg.ptrTy(), entry));
    cg.builder.CreateCondBr(found, foundBlock, exitBlock);
    cg.startBlock(foundBlock);
    // TODO continue iterator
    cg.branchAndStartBlock(exitBlock);
    loop->loopVars[0]->IRValue = cg.builder.CreateStructGEP(getEntryStruct(cg), entry, 0);
    if (loop->loopVars.size() == 2) {
        loop->loopVars[1]->IRValue = cg.builder.CreateStructGEP(getEntryStruct(cg), entry, 1);
    }
}

std::string LgsMap::fmtStr() const {
    return "%s";
}

DIType* LgsMap::getDebugType(LgsCgModule& cg) {
    assert(0);
}
