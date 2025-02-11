#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    static constexpr auto typeName = "Bool";
    static constexpr auto trueLiteral = "true";

    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const override;
    bool operator==(LogosType* other) const override;
    ~LogosBool() override = default;
};

inline const string LogosBool::name() const {
    return typeName;
}

inline Type* LogosBool::getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const {
    return builder->getInt1Ty();
}

inline bool LogosBool::operator==(LogosType* other) const { return true;
    return true;
}

#endif //LOGOSBOOL_H
