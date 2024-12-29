#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"


class LogosInt final : public LogosType {
public:
    int value;
    static constexpr auto name = "Int";

    LogosInt() = default;
    explicit LogosInt(const int value): value(value) {}

    std::string getName() const override;
    ~LogosInt() override = default;
};


#endif //LOGOSINT_H
