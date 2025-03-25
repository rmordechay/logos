#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsConstExpr.h"
#include "types/LgsStr.h"
#include "exprs/unary/LgsIterable.h"

#include <string>

class LgsCharConst;

class LgsStrConst final : public LgsIterable, public LgsConstExpr {
public:
    string value;

    explicit LgsStrConst(const string& value) : LgsConstExpr(new LgsStr()), value(value) {}
    Value* createGlobalStr(Module* module, const std::string& value) const;
    json asJson() override;
    size_t size() override;
    LgsExpr* add(LgsExpr* other) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* add(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
