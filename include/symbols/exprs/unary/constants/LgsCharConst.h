#ifndef LGSCHARCONST_H
#define LGSCHARCONST_H
#include "LgsConstExpr.h"
#include "types/LgsChar.h"

class LgsCharConst final : public LgsConstExpr {
public:
    char value;

    explicit LgsCharConst(const char value) : LgsConstExpr(new LgsChar()), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    json asJson() override;
};

#endif //LGSCHARCONST_H
