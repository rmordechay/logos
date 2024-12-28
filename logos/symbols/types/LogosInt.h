#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LogosType.h"


class LogosInt final : public LogosType {
public:
    static constexpr auto name = "Int";
    int value;
    LogosInt() = default;
    explicit LogosInt(const int value): value(value) {}
    std::string getName() const override;
    LogosType* inferType(LogosType* other) override;
};


#endif //LOGOSINT_H
