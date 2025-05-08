#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsMap.h"
#include <exprs/unary/LgsDArray.h>

Value* LgsIterIndex::createIRValue(CodeGenMetadata* metadata) {
    const auto baseExprType = baseExpr->type;
    if (const auto map = baseExprType->asMap()) {
        return createIRValueFromMap(metadata, map);
    }
    if (const auto arr = baseExprType->asArray()) {
        return createIRValueFromArray(metadata, arr);
    }
    assert(false);
}

Value* LgsIterIndex::getGEP(CodeGenMetadata* metadata) const {
    vector<Value*> IRIndices;
    IRIndices.emplace_back(i32Zero);
    for (const auto& index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(metadata));
    }
    const auto ty = baseExpr->type->getIRType();
    const auto ptr = baseExpr->getIRValue(metadata);
    return metadata->builder.CreateGEP(ty, ptr, IRIndices);
}

void LgsIterIndex::assignIRValue(CodeGenMetadata* metadata, LgsExpr* value) const {
    // TODO make for all indices
    if (const auto map = baseExpr->type->asMap()) {
        map->add.call(metadata, {baseExpr, indices[0]->from, value});
    } else if (const auto arr = baseExpr->type->asArray()) {
        if (arr->isStaticIter) {
            const auto gep = getGEP(metadata);
            const auto rValue = value->getIRValue(metadata);
            metadata->builder.CreateStore(rValue, gep);
        } else {
            arr->add.call(metadata, {baseExpr, indices[0]->from, value});
        }
    }
}


Value* LgsIterIndex::createIRValueFromArray(CodeGenMetadata* metadata, LgsArray* arr) const {
    const auto baseExprIRValue = baseExpr->getIRValue(metadata);
    const auto firstIndex = indices[0]->from;
    if (arr->isStaticIter) {
        const auto iterable = baseExpr->type->asIterable();
        const auto IRType = iterable->getUnderlyingType()->getIRType();
        return metadata->builder.CreateLoad(IRType, getGEP(metadata));
    }
    const auto arrPtrValue = metadata->builder.CreateLoad(ptrTy, baseExprIRValue);
    const auto indexIRValue = firstIndex->getIRValue(metadata);
    const auto rv = arr->get.makeCall(metadata, {arrPtrValue, indexIRValue});
    return metadata->builder.CreateLoad(ptrTy, rv);
}

Value* LgsIterIndex::createIRValueFromMap(CodeGenMetadata* metadata, LgsMap* map) const {
    const auto mapIRType = baseExpr->type->getIRType();
    const auto mapValueIRType = map->kvType.value->getIRType();
    const auto mapPtr = baseExpr->getIRValue(metadata);
    const auto mapLoaded = metadata->builder.CreateLoad(mapIRType, mapPtr);
    const auto indexIRValue = indices[0]->from->getIRValue(metadata);
    const auto rv = map->get.makeCall(metadata, {mapLoaded, indexIRValue});
    return metadata->builder.CreateLoad(mapValueIRType, rv);
}

string LgsIterIndex::getName() {
    return baseExpr->getName();
}

string LgsIterIndex::getNameWithTypes() {
    stringstream str;
    str << getName();
    for (const auto index : indices) {
        str << '[' << index->from->type->prettyName() << ']';
    }
    return str.str();
}

LgsIterIndex::~LgsIterIndex() {
    delete baseExpr;
    for (auto const& index : indices) {
        delete index;
    }
}
