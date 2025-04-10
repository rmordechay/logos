#ifndef LGSFLOATCONST_H
#define LGSFLOATCONST_H
#include "LgsConstExpr.h"
#include "types/LgsFloat.h"

class LgsFloatConst final : public LgsConstExpr {
public:
    double value;

    explicit LgsFloatConst(const float value) : LgsConstExpr(&LOGOS_FLOAT), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsFloatConst() override = default;
};

#endif //LGSFLOATCONST_H
