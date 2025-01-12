#include "LogosInt.h"

std::string LogosInt::getTypeName() const {
    return name;
}

Type* LogosInt::getLLVMType(IRBuilder<>& builder) const {
    return builder.getInt32Ty();
}

Value* LogosInt::getLLVMValue(IRBuilder<>& builder) const {
    return builder.getInt32(value);
}

