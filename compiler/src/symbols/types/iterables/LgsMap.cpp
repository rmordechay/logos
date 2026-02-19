#include "types/iterables/LgsMap.h"
#include "LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsVoid.h"
#include <llvm/IR/Module.h>

#include "LgsConfigs.h"
#include "LgsRTTIndices.h"
#include "Lgs_Exprs.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsFuncType.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsStr.h"

LgsFunc* LgsMap::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto func = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, flags);
        func->fn = [this](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            addIRElement(cg, args[0].expr->IRValue, args[1].expr->IRValue, args[2].expr->IRValue);
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    if (methodName == KEYS_FUNC_NAME) {
        if (methods.contains(KEYS_FUNC_NAME)) return methods[KEYS_FUNC_NAME];
        const auto func = new LgsFunc(KEYS_FUNC_NAME, name, new LgsDArray(pairType->key), {this}, flags);
        func->fn = [](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    if (methodName == VALUES_FUNC_NAME) {
        if (methods.contains(VALUES_FUNC_NAME)) return methods[VALUES_FUNC_NAME];
        const auto func = new LgsFunc(VALUES_FUNC_NAME, name, new LgsDArray(pairType->value), {this}, flags);
        func->fn = [](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    return LgsIterable::getMethod(methodName);
}

Type* LgsMap::getIRType(LgsCodeGen& cg) {
    return cg.getStructType({cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.sizeTy(), cg.sizeTy()}, name);
}

Constant* LgsMap::getRTTypeExtra(LgsCodeGen& cg) {
    const auto rttName = getRTTName() + "_extra";
    const auto st = cg.getStructType({cg.ptrTy(), cg.ptrTy()}, rttName);
    const std::vector args = {pairType->key->getRTType(cg), pairType->value->getRTType(cg)};
    return cg.createGlobal(rttName, st, ConstantStruct::get(st, args));
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
    if (other->isAny()) return true;
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

Value* LgsMap::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    const auto ty = getIRType(cg);
    const auto cap = cg.usize(LGS_ITER_INIT_CAP);
    const auto entriesSize = cg.builder.CreateAdd(pairType->IRSize(cg), cg.usize(sizeof(void*)));
    const auto totalSize = cg.builder.CreateMul(entriesSize, cap);
    const auto ptr = cg.allocInCurrent(IRSize(cg), true);
    const auto entries = cg.allocInCurrent(totalSize, false);
    cg.storeField(ty, ptr, LgsHashMapIndices::type, getRTType(cg));
    cg.storeField(ty, ptr, LgsHashMapIndices::entries, entries);
    cg.storeField(ty, ptr, LgsHashMapIndices::length, cg.zeroSize());
    cg.storeField(ty, ptr, LgsHashMapIndices::cap, cap);
    return ptr;
}

LgsType* LgsMap::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

Value* LgsMap::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.loadField(getIRType(cg), iterable, LgsHashMapIndices::length, cg.sizeTy());
}

Value* LgsMap::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    assert(0);
}

Value* LgsMap::getIRElement(LgsCodeGen& cg, Value* map, Value* index) {
    return cg.builder.CreateCall(getGetFunc(cg), {map, index});
}

void LgsMap::addIRElement(LgsCodeGen& cg, Value* map, Value* index, Value* value) {
    cg.builder.CreateCall(getAddFunc(cg), {map, index, value});
}

Value* LgsMap::getEntryKey(LgsCodeGen& cg, Value* entry) const {
    return cg.builder.CreateStructGEP(baseType->getIRType(cg), entry, LgsHashMapIndices::key);
}

Value* LgsMap::getEntryValue(LgsCodeGen& cg, Value* entry) const {
    return cg.builder.CreateStructGEP(baseType->getIRType(cg), entry, LgsHashMapIndices::value);
}

Value* LgsMap::getEntryNext(LgsCodeGen& cg, Value* entry) const {
    return cg.builder.CreateStructGEP(baseType->getIRType(cg), entry, LgsHashMapIndices::next);
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

void LgsMap::setLoopIRVars(LgsCodeGen& cg, LgsForeachLoop* loop) {
    const auto map = loop->iterExpr->IRValue;
    const auto mapTy = getIRType(cg);
    const auto checkEntryBlock = cg.createBlock("check_entry");
    const auto notFoundEntryBlock = cg.createBlock("not_found_entry");
    const auto foundEntryBlock = cg.createBlock("found_entry");
    const auto entries = cg.loadField(mapTy, map, LgsHashMapIndices::entries, cg.ptrTy());

    // Check entry
    cg.branchAndStartBlock(checkEntryBlock);
    const auto index = cg.loadSize(loop->iteratorCounter);
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, index);
    const auto entry = cg.loadPtr(entryPtr);
    const auto hasEntry = cg.builder.CreateIsNotNull(entry);
    cg.builder.CreateCondBr(hasEntry, foundEntryBlock, notFoundEntryBlock);

    // Not found entry
    cg.startBlock(notFoundEntryBlock);

    const auto incIterator = cg.builder.CreateAdd(index, cg.usize(1));
    cg.store(incIterator, loop->iteratorCounter);
    cg.builder.CreateBr(checkEntryBlock);

    // Found entry
    cg.startBlock(foundEntryBlock);
    const auto currentEntryLoad = cg.loadPtr(entryPtr);
    loop->loopVars[0]->IRValue = getEntryKey(cg, currentEntryLoad);
    if (loop->loopVars.size() == 2) {
        loop->loopVars[1]->IRValue = getEntryValue(cg, currentEntryLoad);
    }
}

std::string LgsMap::fmtStr() const {
    return "%s";
}

DIType* LgsMap::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

Function* LgsMap::getGetFunc(LgsCodeGen& cg) {
    const auto funcName = getName() + "_" + GET_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto keyTy = pairType->key->getStorageType(cg);
    const auto valueTy = pairType->value->getStorageType(cg);
    const std::vector<Type*> params = {cg.ptrTy(), keyTy};
    const auto ft = cg.getFT(valueTy, params);
    if (cg.mode == CG_MODE_SRC) {
        return cg.getFunc(funcName, ft);
    }

    const auto func = cg.getFunc(funcName, ft);
    const auto entryNullCheckBlock = cg.createBlock("entry_null_check");
    const auto entryNullBlock = cg.createBlock("entry_is_null");
    const auto keyCompareBlock = cg.createBlock("keys_compare");
    const auto keysEqualBlock = cg.createBlock("keys_equal");
    const auto keysNotEqualBlock = cg.createBlock("keys_not_equal");

    cg.startFunc(func);
    const auto mapIR = func->getArg(0);
    const auto keyIR = func->getArg(1);

    const auto cap = cg.loadField(getIRType(cg), mapIR, LgsHashMapIndices::cap, cg.sizeTy());
    const auto hash = cg.builder.CreateURem(pairType->key->hashValue(cg, keyIR), cap);
    const auto entries = cg.loadField(getIRType(cg), mapIR, LgsHashMapIndices::entries, cg.ptrTy());
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {hash});
    const auto entry = cg.loadPtr(entryPtr);
    const auto currentEntryPtr = cg.allocaAndStore(cg.ptrTy(), entry, "entry");

    // Entry null check
    cg.branchAndStartBlock(entryNullCheckBlock);
    auto currentEntry = cg.loadPtr(currentEntryPtr);
    const auto isEntryNull = cg.builder.CreateIsNull(currentEntry);
    cg.builder.CreateCondBr(isEntryNull, entryNullBlock, keyCompareBlock);

    // Entry null
    cg.startBlock(entryNullBlock);
    cg.builder.CreateRet(ConstantAggregateZero::get(valueTy));

    // Keys comparison
    cg.startBlock(keyCompareBlock);
    currentEntry = cg.loadPtr(currentEntryPtr);
    const auto keyLoad = cg.load(keyTy, getEntryKey(cg, currentEntry));
    const auto keysEqual = eqIR(cg, keyIR, keyLoad, pairType->key);
    cg.builder.CreateCondBr(keysEqual, keysEqualBlock, keysNotEqualBlock);

    // Keys not equal
    cg.startBlock(keysNotEqualBlock);
    currentEntry = cg.loadPtr(currentEntryPtr);
    const auto nextPtr = getEntryNext(cg, currentEntry);
    const auto next = cg.loadPtr(nextPtr);
    cg.store(next, currentEntryPtr);
    cg.builder.CreateBr(entryNullCheckBlock);

    // Keys equal
    cg.startBlock(keysEqualBlock);
    currentEntry = cg.loadPtr(currentEntryPtr);
    cg.builder.CreateRet(getEntryValue(cg, currentEntry));
    return func;
}

Function* LgsMap::getAddFunc(LgsCodeGen& cg) {
    const auto funcName = getName() + "_" + ADD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto keyType = pairType->key->getStorageType(cg);
    const auto valueTy = pairType->value->getStorageType(cg);
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), keyType, valueTy});
    if (cg.mode == CG_MODE_SRC) {
        return cg.getFunc(funcName, ft);
    }

    const auto func = cg.getFunc(funcName, ft);
    const auto resizeBlock = cg.createBlock("resize");
    const auto checkSlotBlock = cg.createBlock("check_slot");
    const auto entryNullCondBlock = cg.createBlock("entry_null_cond");
    const auto storeElementBlock = cg.createBlock("store_element");
    const auto keyCompareBlock = cg.createBlock("keys_compare");
    const auto equalBlock = cg.createBlock("equal");
    const auto notEqualBlock = cg.createBlock("not_equal");
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);

    cg.startFunc(func);
    const auto mapIR = func->getArg(0);
    const auto keyIR = func->getArg(1);
    const auto valueIR = func->getArg(2);

    const auto mapTy = getIRType(cg);
    const auto entryTy = baseType->getIRType(cg);

    const auto entriesField = cg.builder.CreateStructGEP(mapTy, mapIR, LgsHashMapIndices::entries);
    const auto lenField = cg.builder.CreateStructGEP(mapTy, mapIR, LgsHashMapIndices::length);
    const auto capField = cg.builder.CreateStructGEP(mapTy, mapIR, LgsHashMapIndices::cap);
    const auto level = cg.builder.CreateSub(cg.getCurrentLevel(), cg.usize(1));

    // Resize
    auto len = cg.loadSize(lenField);
    auto cap = cg.loadSize(capField);
    const auto cond = cg.builder.CreateICmpUGE(len, cap);
    cg.builder.CreateCondBr(cond, resizeBlock, checkSlotBlock);

    cg.startBlock(resizeBlock);
    const auto size = cg.builder.CreateMul(pairType->IRSize(cg), cg.usize(sizeof(void*)));
    const auto newCap = cg.builder.CreateMul(size, cg.builder.CreateMul(cap, cg.usize(2)));
    const auto newEntries = cg.allocInLevel(newCap, level, false);
    auto entries = cg.loadPtr(entriesField);

    cg.loop(cap, [&](Value* iValue, BasicBlock* bb) {
        bb->setName("resize_exit");
        auto entry = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {iValue});
        entry = cg.loadPtr(entry);
        const auto hash = cg.builder.CreateURem(pairType->key->hashValue(cg, entry), newCap);
        const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), newEntries, {hash});
        cg.store(entry, entryPtr);
    });
    cg.store(newEntries, entriesField);
    cg.store(newCap, capField);
    cg.branchAndStartBlock(checkSlotBlock);

    // Check slot
    cap = cg.loadSize(capField);
    entries = cg.loadPtr(entriesField);
    const auto hash = cg.builder.CreateURem(pairType->key->hashValue(cg, keyIR), cap);
    const auto entryPtr = cg.builder.CreateInBoundsGEP(cg.ptrTy(), entries, {hash});
    const auto entry = cg.loadPtr(entryPtr);
    const auto entryAlloca = cg.allocaAndStore(cg.ptrTy(), entry);
    const auto entryPtrAlloca = cg.allocaAndStore(cg.ptrTy(), entryPtr);

    cg.branchAndStartBlock(entryNullCondBlock);
    auto entryLoad = cg.loadPtr(entryAlloca);
    const auto isEntryNull = cg.builder.CreateIsNull(entryLoad);
    cg.builder.CreateCondBr(isEntryNull, storeElementBlock, keyCompareBlock);

    // Keys with same hash
    cg.startBlock(keyCompareBlock);
    entryLoad = cg.loadPtr(entryAlloca);
    const auto keysAreEqual = eqIR(cg, keyIR, getEntryKey(cg, entryLoad), pairType->key);
    cg.builder.CreateCondBr(keysAreEqual, equalBlock, notEqualBlock);

    // Keys equal
    cg.startBlock(equalBlock);
    entryLoad = cg.loadPtr(entryAlloca);
    cg.storeField(entryTy, entryLoad, LgsHashMapIndices::value, valueIR);
    cg.builder.CreateRetVoid();

    // Keys not equal
    cg.startBlock(notEqualBlock);
    const auto next = getEntryNext(cg, entry);
    cg.store(next, entryPtrAlloca);
    const auto nextLoad = cg.loadPtr(next);
    cg.store(nextLoad, entryAlloca);
    cg.builder.CreateBr(entryNullCondBlock);

    // Store entry
    cg.startBlock(storeElementBlock);
    const auto newEntry = cg.allocInLevel(size, level, false);
    cg.storeField(entryTy, newEntry, LgsHashMapIndices::key, keyIR);
    cg.storeField(entryTy, newEntry, LgsHashMapIndices::value, valueIR);
    cg.storeField(entryTy, newEntry, LgsHashMapIndices::next, cg.null());
    cg.store(newEntry, cg.loadPtr(entryPtrAlloca));

    // Increment length
    len = cg.loadSize(lenField);
    const auto inc = cg.builder.CreateAdd(len, cg.usize(1));
    cg.store(inc, lenField);
    cg.branchAndStartBlock(exitBlock);

    cg.builder.CreateRetVoid();
    return func;
}
