#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "types/LgsArrayType.h"
#include <exprs/unary/LgsArray.h>

Value* LgsArrayIndex::createIRValue(CodeGenMetadata* metadata) {
    LgsExpr* leftExpr = baseExpr;
    Value* IRValue = nullptr;
    for (int i = 0; i < indexExprs.size(); ++i) {
        const auto index = indexExprs[i]->getIRValue(metadata);
        if (const auto array = leftExpr->asArray()) {
            IRValue = array->getIRValue(metadata);
        } else if (const auto funcCall = leftExpr->asFuncCall()) {
            IRValue = funcCall->getIRValue(metadata);
        } else if (const auto arrayIndex = leftExpr->asArrayIndex()) {
            IRValue = arrayIndex->getIRValue(metadata);
        } else if (const auto var = leftExpr->asVariable()) {
            IRValue = var->getIRValue(metadata);
        } else {
            assert(false && "array index case not implemented");
        }
        const auto arrayType = dynamic_cast<LgsArrayType*>(leftExpr->type);
        indexExprs[i]->setIRValue(arrayType->getIRFuncGetElement(metadata, IRValue, index)),
        leftExpr = indexExprs[i];
    }
    return lastExpr()->getIRValue(metadata);
}

string LgsArrayIndex::getName() {
    return baseExpr->getName();
}

LgsExpr* LgsArrayIndex::lastExpr() const {
    if (indexExprs.empty()) return nullptr;
    return indexExprs[indexExprs.size() - 1];
}

LgsArrayIndex::~LgsArrayIndex() {
    delete baseExpr;
    for (const auto& indexExpr : indexExprs) {
        delete indexExpr;
    }
}
