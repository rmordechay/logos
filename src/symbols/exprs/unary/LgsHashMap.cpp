#include "exprs/unary/LgsHashMap.h"

Value* LgsHashMap::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.CreateAlloca(ptrTy);
}
