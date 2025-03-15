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

    explicit LgsStrConst(const std::string& value) : LgsConst(&LOGOS_STR), value(value) {
        initStr(value);
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    void iterate(CodeGenMetadata* metadata) override;
    size_t size() override;
    void cleanStr(const std::string& value);
    void initStr(const std::string& value);
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
