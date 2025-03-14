#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "unary/LgsIterable.h"

#include <string>

class LgsStringConst final : public LgsIterable {
public:
    std::string value;

    explicit LgsStringConst(const std::string& value) : value(value) {}
    size_t size() override;
    ~LgsStringConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
