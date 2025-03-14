#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsConstant.h"
#include "types/LgsString.h"
#include "unary/LgsIterable.h"

#include <string>

class LgsStrConst final : public LgsIterable, public LgsConstant {
public:
    std::string value;

    explicit LgsStrConst(const std::string& value) : LgsConstant(&LOGOS_STRING), value(value) { cleanStr(value); }
    void cleanStr(const std::string& value);
    Value* createIRValue(CodeGenMetadata* metadata) override;
    size_t size() override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
