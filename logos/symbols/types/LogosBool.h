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
    std::string getName() const override;
    LogosType* inferType(LogosType* other) override;
};

#endif //LOGOSBOOL_H
