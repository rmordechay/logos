#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodeGenMetadata* metadata) {
    const auto hashMap = metadata->builder.CreateAlloca(ptrTy);
    metadata->builder.CreateStore(null, hashMap);
    return hashMap;
}
