#include "exprs/unary/LgsIterIndex.h"
#include <exprs/unary/LgsArrayExpr.h>
#include "types/LgsMap.h"

Value* LgsIterIndex::createIRValue(LgsRuntime* runtime) {
    const auto baseExprType = baseExpr->type;
    if (const auto arr = baseExprType->asArray()) {
        if (arr->isStatic) return getGEP(runtime);
        return getIRFromDynArray(runtime, arr);
    }
    if (const auto map = baseExprType->asMap()) {
        return getIRFromMap(runtime, map);
    }
    if (baseExprType->asStr()) {
        return getIRFromStr(runtime);
    }
    assert(false);
}

Value* LgsIterIndex::getIRFromDynArray(LgsRuntime* runtime, LgsArray* arr) const {
    auto& builder = runtime->builder;
    const auto arrPtr = baseExpr->getIRValue(runtime);
    auto indexIRValue = index->from->getIRValue(runtime);
    indexIRValue = builder.CreateZExt(indexIRValue, builder.getInt64Ty());
    const auto ptrTy = builder.getPtrTy();
    const auto ptr = builder.CreateAlloca(ptrTy);
    builder.CreateStore(arrPtr, ptr);
    const auto load = builder.CreateLoad(ptrTy, ptr);
    return arr->getFunc.callIR(runtime, {load, indexIRValue});
}

Value* LgsIterIndex::getIRFromMap(LgsRuntime* runtime, LgsMap* map) const {
    const auto mapPtr = baseExpr->getIRValue(runtime);
    const auto key = index->from->getIRValue(runtime);
    const auto keyIRType = key->getType();
    const auto keyPtr = runtime->builder.CreateAlloca(keyIRType);
    runtime->builder.CreateStore(key, keyPtr);
    const auto keyLoad = runtime->builder.CreateLoad(keyIRType, keyPtr);
    return map->getFunc.callIR(runtime, {mapPtr, keyLoad});
}

Value* LgsIterIndex::getIRFromStr(LgsRuntime* runtime) const {
    const auto baseExprIRValue = baseExpr->getIRValue(runtime);
    const auto baseExprIRType = baseExpr->type->getIRType();
    if (const auto global = dyn_cast<GlobalVariable>(baseExprIRValue)) {
        const auto ty = global->getValueType();
        const auto value = index->from->getIRValue(runtime);
        return runtime->builder.CreateGEP(ty, baseExprIRValue, {runtime->builder.getInt32(0), value});
    }
    const auto ptr = runtime->builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = runtime->builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    runtime->builder.CreateStore(vaArgInst, ptr);
    return runtime->builder.CreateLoad(baseExprIRType, ptr);
}

void LgsIterIndex::storeHashMap(LgsRuntime* runtime, LgsHashMap* hashMap) const {
    assert(false);
}

void LgsIterIndex::storeScalar(LgsRuntime* runtime, LgsExpr* value) {
    const auto rIRValue = value->getIRValue(runtime);
    const auto baseIRValue = baseExpr->getIRValue(runtime);
    if (const auto arr = baseExpr->type->asArray()) {
        if (!arr->isStatic) {
            const auto ptr = runtime->builder.CreateAlloca(value->type->getIRType());
            runtime->builder.CreateStore(rIRValue, ptr);
            arr->putFunc.callIR(runtime, {baseIRValue, index->from->getIRValue(runtime), ptr});
        } else {
            runtime->builder.CreateStore(rIRValue, getGEP(runtime));
        }
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        const auto key = index->from->getIRValue(runtime);
        const auto keyIRType = key->getType();
        const auto keyPtr = runtime->builder.CreateAlloca(keyIRType);
        runtime->builder.CreateStore(key, keyPtr);
        const auto keyLoad = runtime->builder.CreateLoad(keyIRType, keyPtr);
        map->addFunc.callIR(runtime, {baseIRValue, keyLoad, rIRValue});
    } else {
        const auto iterPtr = getIRValue(runtime);
        runtime->builder.CreateStore(rIRValue, iterPtr);
    }
}

void LgsIterIndex::storeArray(LgsRuntime* runtime, const LgsArrayExpr* arr) const {
    if (!arr->arrType.isStatic) assert(false);
    const auto IRType = baseExpr->type->getIRType();
    const auto arrPtr = baseExpr->getIRValue(runtime);
    vector<Value*> IRIndices = {runtime->builder.getInt32(0)};
    vector<LgsIndex*> indices;
    setIterIndices(this, indices);
    for (const auto index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(runtime));
    }
    for (int i = 0; i < arr->initialElements.size(); ++i) {
        const auto element = arr->initialElements[i];
        const auto IRIndex = runtime->builder.getInt32(i);
        IRIndices.push_back(IRIndex);
        const auto gep = runtime->builder.CreateGEP(IRType, arrPtr, IRIndices);
        const auto rValue = element->getIRValue(runtime);
        runtime->builder.CreateStore(rValue, gep);
        IRIndices.pop_back();
    }
}

Value* LgsIterIndex::getGEP(LgsRuntime* runtime) const {
    vector<Value*> IRIndices = {};
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto irValue = iterIndex->index->from->getIRValue(runtime);
        IRIndices.push_back(irValue);
        const auto innerIterIndex = iterIndex->baseExpr->asIterIndex();
        if (innerIterIndex) {
            iterIndex = innerIterIndex;
        } else {
            ptr = iterIndex->baseExpr->getIRValue(runtime);
            ty = iterIndex->baseExpr->type->getIRType();
            IRIndices.push_back(runtime->builder.getInt32(0));
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return runtime->builder.CreateGEP(ty, ptr, IRIndices);
}

void LgsIterIndex::setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices) {
    while (iterIndex) {
        if (iterIndex->index) {
            indices.push_back(iterIndex->index);
        }
        iterIndex = iterIndex->baseExpr->asIterIndex();
    }
    reverse(indices.begin(), indices.end());
}

string LgsIterIndex::getName() {
    return baseExpr->getName();
}

string LgsIterIndex::prettyName() {
    stringstream str;
    str << baseExpr->prettyName();
    str << '[' << index->from->prettyName() << ']';
    return str.str();
}

LgsIterIndex::~LgsIterIndex() {
    delete baseExpr;
    delete index->from;
    delete index->to;
    delete index;
}
