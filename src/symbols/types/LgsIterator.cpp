#include "types/LgsIterator.h"

#include "utils/LgsUtils.h"

StructType* LgsIterator::getStructType() {
    const auto i64 = IntegerType::getInt64Ty(context);
    const auto ptr = PointerType::getUnqual(context);
    return getIRStructType(name, {ptr, i64, ptr, ptr, ptr, ptr});
}

Value* LgsIterator::createIRValue(LgsRuntime* runtime) {
    assert(0);
}
