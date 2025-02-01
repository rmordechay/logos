#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"

#define INT_TYPE_NAME "Int"

class LogosInt final : public LogosType {
public:
    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder) const override;
    bool operator==(LogosType* other) const override;
    ~LogosInt() override = default;
};

inline const string LogosInt::name() const {
    return INT_TYPE_NAME;
}

inline Type* LogosInt::getLLVMType(IRBuilder<>* builder) const {
    return builder->getInt32Ty();
}

inline bool LogosInt::operator==(LogosType* other) const {
    return this->name() == other->name();
}

inline LogosInt LOGOS_INT;

#endif //LOGOSINT_H
