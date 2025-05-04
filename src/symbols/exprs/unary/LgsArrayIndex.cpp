#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include <exprs/unary/LgsDArray.h>

Value* LgsArrayIndex::createIRValue(CodeGenMetadata* metadata) {
    const auto irType = baseExpr->type->getUnderlyingType()->getIRType();
    return metadata->builder.CreateLoad(irType, getGEP(metadata));
}

Value* LgsArrayIndex::getGEP(CodeGenMetadata* metadata) const {
    vector<Value*> IRIndices;
    IRIndices.emplace_back(metadata->builder.getInt32(0));
    for (const auto& index : indices) {
        IRIndices.emplace_back(index->from->getIRValue(metadata));
    }
    const auto ty = baseExpr->type->getIRType();
    const auto ptr = baseExpr->getIRValue(metadata);
    return metadata->builder.CreateGEP(ty, ptr, IRIndices);
}

string LgsArrayIndex::getName() {
    return baseExpr->getName();
}

string LgsArrayIndex::getNameWithTypes() {
    stringstream str;
    str << getName();
    for (const auto index : indices) {
        str << '[' << index->from->type->getName() << ']';
    }
    return str.str();
}

LgsArrayIndex::~LgsArrayIndex() {
    delete baseExpr;
    for (auto const& index : indices) {
        delete index;
    }
}
