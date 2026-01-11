#include "types/iterables/LgsMap.h"
#include "LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"
#include <llvm/IR/Module.h>
#include "Lgs_Exprs.h"

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
    return sizeof(Lgs_HashMap);
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

Value* LgsMap::getIRZeroValue(LgsCgModule& cg, Value* pointee, const bool levelAbove) {
    const auto ty = getIRType(cg);
    const auto ptr = pointee ? pointee : cg.heapAlloc(cg.usize(sizeBytes()), levelAbove);
    const auto cap = cg.usize(INITIAL_CAPACITY);
    const auto entriesSize = cg.usize(pairType->sizeBytes() + sizeof(void*));
    const auto totalSize = cg.builder.CreateMul(entriesSize, cap);
    const auto entries = cg.heapAlloc(totalSize, levelAbove);
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

Value* LgsMap::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.loadStructField(getIRType(cg), iterable, 1, cg.sizeTy());
}

Value* LgsMap::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}

Value* LgsMap::getIRElement(LgsCgModule& cg, LgsExpr* map, LgsExpr* index) {
    return cg.builder.CreateCall(generateGetFunc(cg), {map->IRValue, index->IRValue});
}

void LgsMap::addIRElement(LgsCgModule& cg, LgsExpr* map, LgsExpr* index, LgsExpr* value) {
    cg.builder.CreateCall(generateAddFunc(cg), {map->IRValue, index->IRValue, value->IRValue});
}

StructType* LgsMap::getEntryStruct(LgsCgModule& cg) const {
    const auto keyTy = pairType->key->getIRType(cg);
    const auto valueTy = pairType->value->getIRType(cg);
    return cg.getStructType({keyTy, valueTy, cg.ptrTy()}, pairType->getName());
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

Value* LgsMap::getNewEntry(LgsCgModule& cg, Value* entryPtr, Value* key, Value* value) const {
    const auto entryTy = getEntryStruct(cg);
    const auto entry = cg.heapAlloc(cg.usize(pairType->sizeBytes() + sizeof(void*)));
    cg.storeStructField(entryTy, entry, 0, key);
    cg.storeStructField(entryTy, entry, 1, value);
    cg.storeStructField(entryTy, entry, 2, cg.null());
    cg.store(entry, entryPtr);
    return entry;
}

bool LgsMap::unpackLoopVars(LgsForeachLoop* loop) const {
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

void LgsMap::setLoopIRVars(LgsCgModule& cg, LgsForeachLoop* loop) {
    const auto map = loop->iterExpr->IRValue;
    const auto mapTy = getIRType(cg);
    const auto checkEntryBlock = cg.createBlock("check_entry");
    const auto notFoundEntryBlock = cg.createBlock("not_found_entry");
    const auto foundEntryBlock = cg.createBlock("found_entry");
    const auto entries = cg.loadStructField(mapTy, map, 0, cg.ptrTy());

    // Check entry
    cg.branchAndStartBlock(checkEntryBlock);
    const auto index = cg.load(cg.sizeTy(), loop->iteratorCounter);
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, index);
    const auto entry = cg.load(cg.ptrTy(), entryPtr);
    const auto hasEntry = cg.builder.CreateIsNotNull(entry);
    cg.builder.CreateCondBr(hasEntry, foundEntryBlock, notFoundEntryBlock);

    // Not found entry
    cg.startBlock(notFoundEntryBlock);

    const auto incIterator = cg.builder.CreateAdd(index, cg.usize(1));
    cg.store(incIterator, loop->iteratorCounter);
    cg.builder.CreateBr(checkEntryBlock);

    // Found entry
    cg.startBlock(foundEntryBlock);
    const auto currentEntryLoad = cg.load(cg.ptrTy(), entryPtr);
    loop->loopVars[0]->IRValue = getEntryKey(cg, currentEntryLoad);
    if (loop->loopVars.size() == 2) {
        loop->loopVars[1]->IRValue = getEntryValue(cg, currentEntryLoad);
    }
}

std::string LgsMap::fmtStr() const {
    return "%s";
}

DIType* LgsMap::getDebugType(LgsCgModule& cg) {
    assert(0);
}

Function* LgsMap::generateGetFunc(LgsCgModule& cg) {
    const auto funcName = getName() + "_" + GET_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;

    const auto keyTy = pairType->key->getTypeOrPtr(cg);
    const auto valueTy = pairType->value->getTypeOrPtr(cg);
    const std::vector<Type*> params = {cg.ptrTy(), keyTy};
    const auto ft = cg.getFT(valueTy, params);
    if (cg.mode == CG_MODE_SRC_CODE) {
        return cg.getFunc(funcName, ft);
    }

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;
    const auto func = cg.getFunc(funcName, ft);
    cg.currentFunc = func;

    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    const auto entryNullCheckBlock = cg.createBlock("entry_null_check");
    const auto entryNullBlock = cg.createBlock("entry_is_null");
    const auto keyCompareBlock = cg.createBlock("keys_compare");
    const auto keysEqualBlock = cg.createBlock("keys_equal");
    const auto keysNotEqualBlock = cg.createBlock("keys_not_equal");

    cg.builder.SetInsertPoint(entryBlock);
    const auto mapIR = cg.currentFunc->getArg(0);
    const auto keyIR = cg.currentFunc->getArg(1);
    const auto indexTemp = pairType->key->getZeroValue();
    indexTemp->IRValue = keyIR;

    const auto cap = loadCapField(cg, mapIR);
    const auto hash = cg.builder.CreateURem(indexTemp->hashValue(cg), cap);
    const auto entries = loadEntriesField(cg, mapIR);
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {hash});
    const auto entry = cg.load(cg.ptrTy(), entryPtr);
    const auto keyPtr = getEntryKey(cg, entry);
    const auto currentEntryPtr = cg.allocaAndStore(cg.ptrTy(), entry, "entry");

    // Entry null check
    cg.branchAndStartBlock(entryNullCheckBlock);
    auto currentEntry = cg.load(cg.ptrTy(), currentEntryPtr);
    const auto isEntryNull = cg.builder.CreateIsNull(currentEntry);
    cg.builder.CreateCondBr(isEntryNull, entryNullBlock, keyCompareBlock);

    // Entry null
    cg.startBlock(entryNullBlock);
    cg.builder.CreateRet(pairType->value->getIRZeroValue(cg));

    // Keys comparison
    cg.startBlock(keyCompareBlock);
    const auto indexTemp2 = pairType->key->getZeroValue();
    indexTemp2->IRValue = cg.load(keyTy, keyPtr);
    const auto keysEqual = eqIR(cg, indexTemp, indexTemp2);
    cg.builder.CreateCondBr(keysEqual, keysEqualBlock, keysNotEqualBlock);

    // Keys not equal
    cg.startBlock(keysNotEqualBlock);
    currentEntry = cg.load(cg.ptrTy(), currentEntryPtr);
    const auto nextPtr = getEntryNext(cg, currentEntry);
    const auto next = cg.load(cg.ptrTy(), nextPtr);
    cg.store(next, currentEntryPtr);
    cg.builder.CreateBr(entryNullCheckBlock);

    // Keys equal
    cg.startBlock(keysEqualBlock);
    cg.builder.CreateRet(cg.load(valueTy, getEntryValue(cg, entry)));

    // Epilogue
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    freeExpr(indexTemp);
    freeExpr(indexTemp2);

    return func;
}

Function* LgsMap::generateAddFunc(LgsCgModule& cg) {
    const auto funcName = getName() + "_" + ADD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;

    const auto valueTy = pairType->value->getTypeOrPtr(cg);
    const auto keyType = pairType->key->getTypeOrPtr(cg);
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), keyType, valueTy});
    if (cg.mode == CG_MODE_SRC_CODE) {
        return cg.getFunc(funcName, ft);
    }

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;
    const auto func = cg.getFunc(funcName, ft);
    cg.currentFunc = func;

    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    const auto resizeBlock = cg.createBlock("resize");
    const auto checkSlotBlock = cg.createBlock("check_slot");
    const auto entryNullCondBlock = cg.createBlock("entry_null_cond");
    const auto storeElementBlock = cg.createBlock("store_element");
    const auto keyCompareBlock = cg.createBlock("keys_compare");
    const auto equalBlock = cg.createBlock("equal");
    const auto notEqualBlock = cg.createBlock("not_equal");

    cg.builder.SetInsertPoint(entryBlock);
    const auto mapIR = cg.currentFunc->getArg(0);
    const auto keyIR = cg.currentFunc->getArg(1);
    const auto valueIR = cg.currentFunc->getArg(2);

    const auto mapTy = getIRType(cg);
    const auto entryTy = getEntryStruct(cg);
    const auto indexTemp = pairType->key->getZeroValue();

    const auto entriesField = cg.builder.CreateStructGEP(mapTy, mapIR, 0);
    const auto lenField = cg.builder.CreateStructGEP(mapTy, mapIR, 1);
    const auto capField = cg.builder.CreateStructGEP(mapTy, mapIR, 2);

    // Resize
    auto len = cg.load(cg.sizeTy(), lenField);
    auto cap = cg.load(cg.sizeTy(), capField);
    const auto cond = cg.builder.CreateICmpUGE(len, cap);
    cg.builder.CreateCondBr(cond, resizeBlock, checkSlotBlock);

    cg.startBlock(resizeBlock);
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
    cg.freeValue(entries);
    cg.store(newEntries, entriesField);
    cg.store(newCap, capField);
    cg.branchAndStartBlock(checkSlotBlock);

    // Check slot
    indexTemp->IRValue = keyIR;
    cap = cg.load(cg.sizeTy(), capField);
    entries = cg.load(cg.ptrTy(), entriesField);
    const auto hash = cg.builder.CreateURem(indexTemp->hashValue(cg), cap);
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {hash});
    const auto entry = cg.load(cg.ptrTy(), entryPtr);
    const auto entryAlloca = cg.allocaAndStore(cg.ptrTy(), entry);
    const auto entryPtrAlloca = cg.allocaAndStore(cg.ptrTy(), entryPtr);

    cg.branchAndStartBlock(entryNullCondBlock);
    const auto entryLoad = cg.load(cg.ptrTy(), entryAlloca);
    const auto isNotNull = cg.builder.CreateIsNotNull(entryLoad);
    cg.builder.CreateCondBr(isNotNull, keyCompareBlock, storeElementBlock);

    // Keys with same hash
    cg.startBlock(keyCompareBlock);
    const auto loadKey = cg.load(pairType->key->getIRType(cg), getEntryKey(cg, entry));
    const auto indexTemp2 = pairType->key->getZeroValue();
    indexTemp2->IRValue = loadKey;
    cg.builder.CreateCondBr(eqIR(cg, indexTemp, indexTemp2), equalBlock, notEqualBlock);

    // Keys equal
    cg.startBlock(equalBlock);
    cg.storeStructField(entryTy, entry, 1, valueIR);
    cg.builder.CreateRetVoid();

    // Keys not equal
    cg.startBlock(notEqualBlock);
    const auto next = getEntryNext(cg, entry);
    cg.store(next, entryPtrAlloca);
    cg.store(cg.load(cg.ptrTy(), next), entryAlloca);
    cg.builder.CreateBr(entryNullCondBlock);

    // Store entry
    cg.startBlock(storeElementBlock);
    const auto newEntry = cg.heapAlloc(cg.usize(pairType->sizeBytes() + sizeof(void*)));
    cg.storeStructField(entryTy, newEntry, 0, keyIR);
    cg.storeStructField(entryTy, newEntry, 1, valueIR);
    cg.storeStructField(entryTy, newEntry, 2, cg.null());
    cg.store(newEntry, cg.load(cg.ptrTy(), entryPtrAlloca));

    // Increment length
    len = cg.load(cg.sizeTy(), lenField);
    const auto inc = cg.builder.CreateAdd(len, cg.usize(1));
    cg.store(inc, lenField);

    // Epilogue
    cg.builder.CreateRetVoid();
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    freeExpr(indexTemp);
    freeExpr(indexTemp2);

    return func;
}
