#ifndef PRINT_H
#define PRINT_H
#include "LogosFunc.h"
#include "types/LogosInt.h"


class LogosPrint final : public LogosFunc {
public:
    static constexpr auto name = "print";

    explicit LogosPrint() : LogosFunc(name, LogosInt()) {}
    ~LogosPrint() override = default;
};

#endif //PRINT_H
