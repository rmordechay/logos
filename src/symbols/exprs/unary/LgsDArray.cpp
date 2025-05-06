#include "exprs/unary/LgsDArray.h"

Value* LgsDArray::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto constantInt = builder.getInt64(sizeof(void*));
    const auto size = initialElements.empty() ? 2 : initialElements.size();
    const auto capacity = builder.getInt32(size);

    IRValue = builder.CreateAlloca(ptrTy);
    const auto rt = arrType.new_.call(metadata, {capacity, constantInt});
    builder.CreateStore(rt, IRValue);

    for (const auto element : initialElements) {
        arrType.add.call(metadata, {this, element});
    }

    return IRValue;
}
