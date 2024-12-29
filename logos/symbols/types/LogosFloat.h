#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosType.h"


class LogosFloat final : public LogosType {
public:
    float value;
    static constexpr auto name = "Float";

    LogosFloat() = default;
    explicit LogosFloat(const float value): value(value) {}
    std::string getName() const override;
    ~LogosFloat() override = default;
};


#endif //LOGOSFLOAT_H
