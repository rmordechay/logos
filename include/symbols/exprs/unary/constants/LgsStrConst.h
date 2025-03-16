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
    string value;

    explicit LgsStrConst(const string& value) : LgsConst(&LOGOS_STR), value(value) {
        cleanStr();
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    size_t size() override;
    void cleanStr();
    inline Value* add(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* createGlobalStr(Module* module, const std::string& value) const;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
