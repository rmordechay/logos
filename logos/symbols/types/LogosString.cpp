#include "LogosString.h"

std::string LogosString::getTypeName() const {
    return name;
}

Type* LogosString::getLLVMType(IRBuilder<>& builder) const {
    return nullptr;
}

Value* LogosString::getLLVMValue(IRBuilder<>& builder) const {
    return ConstantDataArray::getString(builder.getContext(), value);
}


