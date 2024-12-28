#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosTypedValue.h"


class LogosBool final : public LogosTypedValue {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";
    bool value;

    LogosBool() = default;
    explicit LogosBool(const bool value): value(value) {}

    std::string getName() const override;
    LogosTypedValue* applyOperation(LogosTypedValue* other) override;
    ~LogosBool() override = default;
};

#endif //LOGOSBOOL_H
