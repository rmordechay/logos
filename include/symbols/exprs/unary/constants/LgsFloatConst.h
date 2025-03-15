#ifndef LGSFLOATCONST_H
#define LGSFLOATCONST_H
#include "LgsConst.h"
#include "types/LgsFloat.h"

class LgsFloatConst final : public LgsConst {
public:
    double value;

    explicit LgsFloatConst(const float value) : LgsConst(&LOGOS_FLOAT), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsFloatConst() override = default;
};

#endif //LGSFLOATCONST_H
