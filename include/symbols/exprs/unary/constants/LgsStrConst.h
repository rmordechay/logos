#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsConst.h"
#include "types/LgsStr.h"
#include "exprs/unary/LgsIterable.h"

#include <string>

class LgsCharConst;

class LgsStrConst final : public LgsIterable, public LgsConst {
public:
    string value;

    explicit LgsStrConst(const string& value) : LgsConst(&LOGOS_STR), value(value) {}
    Value* createGlobalStr(Module* module, const std::string& value) const;
    void cleanStr();
    size_t size() override;
    LgsExpr* add(LgsExpr* other) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* add(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
