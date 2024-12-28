#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosTypedValue.h"

#include <string>


class LogosString final : public LogosTypedValue {
public:
    static constexpr auto name = "Str";
    const std::string &value;

    explicit LogosString(const std::string &value): value(value) {}
    std::string getName() const override;
    LogosTypedValue* applyOperation(LogosTypedValue* other) override;
    ~LogosString() override = default;
};



#endif //LOGOSSTRING_H
