#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosType.h"

#include <string>


class LogosString final : public LogosType {
public:
    std::string value;
    static constexpr auto name = "Str";

    explicit LogosString(): value("") {}
    explicit LogosString(const std::string &value): value(value) {}
    std::string getName() const override;
    ~LogosString() override = default;
};



#endif //LOGOSSTRING_H
