#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosType.h"


class LogosFloat final : public LogosType {
public:
    static constexpr auto name = "Float";
    float value;
    LogosFloat() = default;
    explicit LogosFloat(const float value): value(value) {}
    std::string getName() const override;
};


#endif //LOGOSFLOAT_H
