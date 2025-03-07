#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LogosIterable.h"

#include <string>

class LogosStringConst final : public LogosIterable {
public:
    std::string value;

    explicit LogosStringConst(const std::string& value) : value(value) {}
    size_t size() override;
    ~LogosStringConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
