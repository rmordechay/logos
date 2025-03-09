#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosType.h"
#include "LogosValue.h"
#include "exprs/LogosConstant.h"

class LogosFloat final : public LogosType {
public:
    Type* IRType = Type::getFloatTy(context);
    string typeName = "Float";

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosFloat() override = default;
};

inline const string LogosFloat::getName() const {
    return typeName;
}

inline Type* LogosFloat::getIRType() {
    return IRType;
}

inline LogosConstant* LogosFloat::getZeroValue() {
    return new LogosConstant(this, 0.f);
}

inline bool LogosFloat::equals(LogosType* other) const {
    return typeName == other->getName();
}

inline LogosFloat LOGOS_FLOAT;

#endif // LOGOSFLOAT_H
