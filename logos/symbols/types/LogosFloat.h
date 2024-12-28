#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosTypedValue.h"


class LogosFloat final : public LogosTypedValue {
public:
    static constexpr auto name = "Float";
    float value;

    LogosFloat() = default;
    explicit LogosFloat(const float value): value(value) {}
    std::string getName() const override;
    LogosTypedValue* applyOperation(LogosTypedValue* other) override;
    ~LogosFloat() override = default;
};


#endif //LOGOSFLOAT_H
