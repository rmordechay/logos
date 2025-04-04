#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "types/LgsArrayType.h"
#include <exprs/unary/LgsArray.h>

Value* LgsArrayIndex::createIRValue(CodeGenMetadata* metadata) {
    Value* IRValue = expr->getIRValue(metadata);
    if (const auto arrType = dynamic_cast<LgsArrayType*>(expr->type)) {
        return arrType->getIRFuncGetElement(metadata, IRValue, index->getIRValue(metadata));
    }
    return IRValue;
}

string LgsArrayIndex::getName() {
    return expr->getName();
}

LgsArrayIndex::~LgsArrayIndex() {
    delete expr;
    delete index;
}
