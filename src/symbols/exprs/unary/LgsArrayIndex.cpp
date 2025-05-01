#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include <exprs/unary/LgsDArray.h>

Value* LgsArrayIndex::createIRValue(CodeGenMetadata* metadata) {
    Value* IRValue = baseExpr->getIRValue(metadata);
    return IRValue;
}

string LgsArrayIndex::getName() {
    return baseExpr->getName();
}

LgsArrayIndex::~LgsArrayIndex() {
    delete baseExpr;
    for (const auto& index : indices) {
        delete index;
    }
}
