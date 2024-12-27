#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosType.h"

#include <string>
#include <utility>


class LogosString final : public LogosType {
public:
    static constexpr auto name = "Str";
    const std::string &value;
    explicit LogosString(const std::string &value): value(value) {}
};



#endif //LOGOSSTRING_H
