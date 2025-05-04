#include "exprs/unary/LgsSArray.h"

#include "types/LgsIterable.h"

Value* LgsSArray::createIRValue(CodeGenMetadata* metadata) {
    const auto iterable = type->asIterable();
    assert(iterable);
    const auto irType = iterable->getUnderlyingType()->getIRType();
    return metadata->builder.CreateAlloca(irType);
}

size_t LgsSArray::length() const {
    assert(type->asIterable());
    assert(type->asIterable()->sizes.size() > 0);
    return type->asIterable()->sizes[0];
}

void LgsSArray::free(CodeGenMetadata* metadata) {
    assert(false);
}
