#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"

#define INT_TYPE_NAME "Int"

class LogosInt final : public LogosType {
public:
    const string name() const override;
    Type* writeLLVMType(CodeGenMetadata* metadata) override;
    bool operator==(LogosType* other) const override;
    ~LogosInt() override = default;
};

inline const string LogosInt::name() const {
    return INT_TYPE_NAME;
}

inline Type* LogosInt::writeLLVMType(CodeGenMetadata* metadata) {
    if (llvmType) return llvmType;
    llvmType = metadata->builder->getInt32Ty();
    return llvmType;
}

inline bool LogosInt::operator==(LogosType* other) const { return true;
    return this->name() == other->name();
}

inline LogosInt LOGOS_INT;

#endif //LOGOSINT_H
