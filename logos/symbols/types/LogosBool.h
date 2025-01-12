#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosValue.h"


class LogosBool final : public LogosValue {
public:
    bool value;
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";

    explicit LogosBool(const bool value): value(value) {}
    ~LogosBool() override = default;

    std::string getTypeName() const override;
    Type* getLLVMType(IRBuilder<>& builder) const override;
    Value* getLLVMValue(IRBuilder<>& builder) const override;
};

#endif //LOGOSBOOL_H
