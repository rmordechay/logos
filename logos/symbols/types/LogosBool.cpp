#include "LogosBool.h"

std::string LogosBool::getTypeName() const {
    return name;
}

Type* LogosBool::getLLVMType(IRBuilder<>& builder) const {
    return builder.getInt1Ty();
}

Value* LogosBool::getLLVMValue(IRBuilder<>& builder) const {
    return builder.getInt1(value);
}

