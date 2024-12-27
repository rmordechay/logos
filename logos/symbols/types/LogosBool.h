#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LogosType.h"


class LogosBool final : public LogosType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";
    bool value;
    LogosBool() = default;
    explicit LogosBool(const bool value): value(value) {}
};

#endif //LOGOSBOOL_H
