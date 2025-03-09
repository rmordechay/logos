#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosType.h"
#include "LogosValue.h"
#include "exprs/LogosConstant.h"

class LogosBool final : public LogosType {
public:
    Type* IRType = Type::getInt1Ty(context);
    string typeName = "Bool";
    string trueLiteral = "true";

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosBool() override = default;
};

inline const string LogosBool::getName() const {
    return typeName;
}

inline Type* LogosBool::getIRType() {
    return IRType;
}

inline LogosConstant* LogosBool::getZeroValue() {
    return new LogosConstant(this, false);
}

inline bool LogosBool::equals(LogosType* other) const {
    return typeName == other->getName();
}

inline LogosBool LOGOS_BOOL;

#endif // LOGOSBOOL_H
