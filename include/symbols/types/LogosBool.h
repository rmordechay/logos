#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosType.h"
#include "constants/LogosConstant.h"

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

inline LogosBool LOGOS_BOOL;

#endif // LOGOSBOOL_H
