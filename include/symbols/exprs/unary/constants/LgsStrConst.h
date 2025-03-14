#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsCharConst.h"
#include "LgsConst.h"
#include "types/LgsStr.h"
#include "unary/LgsIterable.h"

#include <string>

class LgsCharConst;

class LgsStrConst final : public LgsIterable, public LgsConst {
public:
    std::string value;
    vector<LgsCharConst> chars;

    explicit LgsStrConst(const std::string& value) : LgsConst(&LOGOS_STRING), value(value) {
        cleanStr(value);
        for (const char ch : value) {
            chars.emplace_back(LgsCharConst(ch));
        }
    }

    void cleanStr(const std::string& value);
    Value* createIRValue(CodeGenMetadata* metadata) override;
    size_t size() override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
