#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosTypedValue.h"


class LogosInt final : public LogosTypedValue {
public:
    static constexpr auto name = "Int";
    int value;

    LogosInt() = default;
    explicit LogosInt(const int value): value(value) {}

    std::string getName() const override;
    LogosTypedValue* applyOperation(LogosTypedValue* other) override;
    ~LogosInt() override = default;
};


#endif //LOGOSINT_H
