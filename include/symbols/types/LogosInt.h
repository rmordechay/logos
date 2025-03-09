#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "CodeGenerator.h"
#include "LogosType.h"
#include "exprs/LogosConstant.h"


class LogosInt final : public LogosType {
public:
    Type* IRType = Type::getInt32Ty(context);
    string typeName = "Int";
    LogosConstant zeroValue = LogosConstant(this, 0);

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosInt() override = default;
};

inline const string LogosInt::getName() const {
    return typeName;
}

inline Type* LogosInt::getIRType() {
    return IRType;
}

inline LogosConstant* LogosInt::getZeroValue() {
    return new LogosConstant(this, 0);
}

inline bool LogosInt::equals(LogosType* other) const {
    return typeName == other->getName();
}

inline LogosInt LOGOS_INT;

#endif //LOGOSINT_H
