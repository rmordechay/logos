#ifndef LGSFLOATCONST_H
#define LGSFLOATCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsFloat.h"

class LgsFloatConst final : public LgsConstExpr {
public:
    double value;

    explicit LgsFloatConst(const float value) : LgsConstExpr(&LGS_FLOAT), value(value) {}
    Value* createIRValue(Module* module) override;
    ~LgsFloatConst() override = default;
};

#endif //LGSFLOATCONST_H
