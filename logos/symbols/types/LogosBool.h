#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    Type* getLLVMType(IRBuilder<>* builder) const override {
        return builder->getInt1Ty();
    }
    ~LogosBool() override = default;
};

#endif //LOGOSBOOL_H
