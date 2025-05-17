#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/map/LgsMap.h"
#include <exprs/unary/LgsArrayExpr.h>

Value* LgsIterIndex::createIRValue(CodeGenMetadata* metadata) {
    const auto baseExprType = baseExpr->type;
    if (const auto arr = baseExprType->asArray()) {
        if (baseExprType->isConst) return getGEP(metadata);
        return createIRDynArray(metadata, arr);
    }
    if (const auto map = baseExprType->asMap()) {
        return createMapIRValue(metadata, map);
    }
    if (baseExprType->asStr()) {
        return createStrIRValue(metadata);
    }
    assert(false);
}

Value* LgsIterIndex::getLength(CodeGenMetadata* metadata) {
    const auto dimsExprs = type->asArray()->dimsExprs;
    const auto dimsExpr = dimsExprs[indices.size() - 1];
    return dimsExpr->getIRValue(metadata);
}

Value* LgsIterIndex::getGEP(CodeGenMetadata* metadata) const {
    const auto ty = baseExpr->type->getIRType();
    const auto ptr = baseExpr->getIRValue(metadata);
    vector<Value*> IRIndices;
    IRIndices.push_back(i32Zero);
    for (const auto index : indices) {
        auto value = index->from->getIRValue(metadata);
        IRIndices.push_back(value);
    }
    return metadata->builder.CreateGEP(ty, ptr, IRIndices);
}

void LgsIterIndex::castExpr(LgsType* other) {
    assert(false);
}

Value* LgsIterIndex::createIRDynArray(CodeGenMetadata* metadata, LgsArray* arr) const {
    const auto mapIRType = baseExpr->type->getIRType();
    const auto mapPtr = baseExpr->getIRValue(metadata);
    const auto mapLoaded = metadata->builder.CreateLoad(mapIRType, mapPtr);
    const auto indexIRValue = indices[0]->from->getIRValue(metadata);
    return arr->get.callIR(metadata, {mapLoaded, indexIRValue});
}

Value* LgsIterIndex::createMapIRValue(CodeGenMetadata* metadata, LgsMap* map) const {
    const auto mapIRType = baseExpr->type->getIRType();
    const auto mapPtr = baseExpr->getIRValue(metadata);
    const auto mapLoaded = metadata->builder.CreateLoad(mapIRType, mapPtr);
    const auto indexIRValue = indices[0]->from->getIRValue(metadata);
    return map->get.callIR(metadata, {mapLoaded, indexIRValue});
}

Value* LgsIterIndex::createStrIRValue(CodeGenMetadata* metadata) const {
    const auto ptr = baseExpr->getIRValue(metadata);
    const auto ty = dyn_cast<GlobalVariable>(ptr)->getValueType();
    const auto value = indices[0]->from->getIRValue(metadata);
    return metadata->builder.CreateGEP(ty, ptr, {i32Zero, value});
}

void LgsIterIndex::storeHashMap(CodeGenMetadata* metadata, LgsHashMap* hashMap) const {
    assert(false);
}

void LgsIterIndex::storeScalar(CodeGenMetadata* metadata, LgsExpr* value) {
    if (const auto map = baseExpr->type->asMap()) {
        auto key = indices[0]->from;
        map->add.call(metadata, {baseExpr, key, value});
    } else if (baseExpr->type->asArray() && !baseExpr->type->isConst) {
        assert(false);
    } else {
        const auto gep = getIRValue(metadata);
        const auto rValue = value->getIRValue(metadata);
        metadata->builder.CreateStore(rValue, gep);
    }
}

void LgsIterIndex::storeArray(CodeGenMetadata* metadata, const LgsArrayExpr* arr) const {
    if (!arr->type->isConst) assert(false);
    const auto IRType = baseExpr->type->getIRType();
    const auto arrPtr = baseExpr->getIRValue(metadata);
    vector IRIndices = {i32Zero};
    for (const auto index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(metadata));
    }
    for (int i = 0; i < arr->initialElements.size(); ++i) {
        const auto element = arr->initialElements[i];
        const auto IRIndex = metadata->builder.getInt32(i);
        IRIndices.push_back(IRIndex);
        const auto gep = metadata->builder.CreateGEP(IRType, arrPtr, IRIndices);
        const auto rValue = element->getIRValue(metadata);
        metadata->builder.CreateStore(rValue, gep);
        IRIndices.pop_back();
    }
}

string LgsIterIndex::getName() {
    return baseExpr->getName();
}

string LgsIterIndex::prettyName() {
    stringstream str;
    str << baseExpr->prettyName();
    for (const auto index : indices) {
        str << '[' << index->from->prettyName() << ']';
    }
    return str.str();
}

LgsIterIndex::~LgsIterIndex() {
    delete baseExpr;
    for (auto const& index : indices) {
        delete index;
    }
}
