#ifndef LGSCHARCONST_H
#define LGSCHARCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsChar.h"

class LgsCharConst final : public LgsConstExpr {
public:
    char value;

    explicit LgsCharConst(const char value) : LgsConstExpr(&LGS_CHAR), value(value) {}
    Value* createIRValue(CodegenMetadata* metadata) override;
};

#endif //LGSCHARCONST_H
