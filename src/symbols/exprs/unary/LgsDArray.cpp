#include "exprs/unary/LgsDArray.h"

Value* LgsDArray::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto capacity = initialElements.empty() ? INITIAL_ARRAY_SIZE : initialElements.size() * 2;
    const auto capacityIR = builder.getInt32(capacity);

    IRValue = builder.CreateAlloca(ptrTy);
    const auto constantInt = builder.getInt64(sizeof(void*));
    const auto rt = arrType.new_.makeCall(metadata, {capacityIR, constantInt});
    builder.CreateStore(rt, IRValue);

    for (const auto element : initialElements) {
        arrType.add.call(metadata, {this, element});
    }

    return IRValue;
}
