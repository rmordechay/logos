#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"

#define INT_TYPE_NAME "Int"

class LogosInt final : public LogosType {
public:
    Type* llvmType = Type::getInt32Ty(context);

    const string name() const override;
    Type* getLLVMType() override;
    bool operator==(LogosType* other) const override;
    ~LogosInt() override = default;
};

inline const string LogosInt::name() const {
    return INT_TYPE_NAME;
}

inline Type* LogosInt::getLLVMType() {
    return llvmType;
}

inline bool LogosInt::operator==(LogosType* other) const { return true;
    return this->name() == other->name();
}

inline LogosInt LOGOS_INT;

#endif //LOGOSINT_H
