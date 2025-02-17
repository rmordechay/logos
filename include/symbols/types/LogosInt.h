#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "CodeGenerator.h"
#include "LogosType.h"

#define INT_TYPE_NAME "Int"

class LogosInt final : public LogosType {
public:
    Type* IRType = Type::getInt32Ty(context);

    const string name() const override;
    Type* getIRType() override;
    bool operator==(LogosType* other) const override;
    ~LogosInt() override = default;
};

inline const string LogosInt::name() const {
    return INT_TYPE_NAME;
}

inline Type* LogosInt::getIRType() {
    return IRType;
}

inline bool LogosInt::operator==(LogosType* other) const { return true;
    return this->name() == other->name();
}

inline LogosInt LOGOS_INT;

#endif //LOGOSINT_H
