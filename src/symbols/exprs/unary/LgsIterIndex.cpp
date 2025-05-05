#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsMap.h"

#include <exprs/unary/LgsDArray.h>

Value* LgsIterIndex::createIRValue(CodeGenMetadata* metadata) {
    const auto iterable = baseExpr->type->asIterable();
    const auto irType = iterable->getUnderlyingType()->getIRType();
    return metadata->builder.CreateLoad(irType, getGEP(metadata));
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

void LgsIterIndex::assignIRValue(CodeGenMetadata* metadata, LgsExpr* expr) const {
    if (const auto lgsMap = baseExpr->type->asMap()) {
        lgsMap->insertFunc.call(metadata, {expr});
    } else if (baseExpr->type->asArray()) {
        const auto gep = getGEP(metadata);
        const auto rValue = expr->getIRValue(metadata);
        metadata->builder.CreateStore(rValue, gep);
    }
}

string LgsIterIndex::getName() {
    return baseExpr->getName();
}

string LgsIterIndex::getNameWithTypes() {
    stringstream str;
    str << getName();
    for (const auto index : indices) {
        str << '[' << index->from->type->getPrettyName() << ']';
    }
    return str.str();
}

LgsIterIndex::~LgsIterIndex() {
    delete baseExpr;
    for (auto const& index : indices) {
        delete index;
    }
}
