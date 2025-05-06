#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsMap.h"
#include <exprs/unary/LgsDArray.h>

Value* LgsIterIndex::createIRValue(CodeGenMetadata* metadata) {
    const auto baseExprType = baseExpr->type;
    const auto baseExprIRValue = baseExpr->getIRValue(metadata);
    auto firstIndex = indices[0]->from;
    if (const auto map = baseExprType->asMap()) {
        return map->get.call(metadata, {baseExpr, firstIndex});
    }
    if (const auto arr = baseExprType->asArray()) {
        if (arr->isStatic) {
            const auto iterable = baseExpr->type->asIterable();
            const auto IRType = iterable->getUnderlyingType()->getIRType();
            return metadata->builder.CreateLoad(IRType, getGEP(metadata));
        }
        const auto arrPtrValue = metadata->builder.CreateLoad(ptrTy, baseExprIRValue);
        const auto value = arr->get.call(metadata, {arrPtrValue, firstIndex->getIRValue(metadata)});
        return metadata->builder.CreateLoad(ptrTy, value);
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
        if (arr->isStatic) {
            const auto gep = getGEP(metadata);
            const auto rValue = value->getIRValue(metadata);
            metadata->builder.CreateStore(rValue, gep);
        } else {
            arr->add.call(metadata, {baseExpr, indices[0]->from, value});
        }
    }
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
