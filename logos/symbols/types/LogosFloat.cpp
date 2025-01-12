#include "LogosFloat.h"

std::string LogosFloat::getTypeName() const {
    return name;
}

Type* LogosFloat::getLLVMType(IRBuilder<>& builder) const {
    return builder.getFloatTy();
}

Value* LogosFloat::getLLVMValue(IRBuilder<>& builder) const {
    return ConstantFP::get(getLLVMType(builder), value);
}


