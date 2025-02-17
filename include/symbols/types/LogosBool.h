#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosValue.h"
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    Type* IRType = Type::getInt1Ty(context);
     string typeName = "Bool";
     auto trueLiteral = "true";

    const string name() const override;
    Type* getIRType() override;
    bool operator==(LogosType* other) const override;
    ~LogosBool() override = default;
};

inline const string LogosBool::name() const {
    return typeName;
}

inline void LogosBool::setIRType(Type* type) {

}

inline Type* LogosBool::getIRType() {
    return IRType;
}

inline bool LogosBool::operator==(LogosType* other) const { return true;
    return true;
}

#endif //LOGOSBOOL_H
