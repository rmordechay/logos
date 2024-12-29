#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    bool value;
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LogosBool() = default;
    explicit LogosBool(const bool value): value(value) {}

    std::string getName() const override;
    ~LogosBool() override = default;
};

#endif //LOGOSBOOL_H
