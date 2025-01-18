#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";

    LogosBool() = default;
    ~LogosBool() override = default;

    Type* getLLVMType(IRBuilder<>* builder) const override {
        return builder->getInt1Ty();
    }
};

#endif //LOGOSBOOL_H
