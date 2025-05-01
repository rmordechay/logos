#include "exprs/unary/LgsSArray.h"

Value* LgsSArray::createIRValue(CodeGenMetadata* metadata) {
    const auto iterable = dynamic_cast<LgsIterable*>(type);
    const auto irType = iterable->getUnderlyingIRType();
    return metadata->builder.CreateAlloca(irType);
}

size_t LgsSArray::length() const {
    return arraySize[0];
}

bool LgsSArray::isIterable() {
    return true;
}

void LgsSArray::free(CodeGenMetadata* metadata) {
    assert(false);
}
