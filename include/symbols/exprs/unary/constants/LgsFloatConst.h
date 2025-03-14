#ifndef LGSFLOATCONST_H
#define LGSFLOATCONST_H
#include "LgsConstant.h"
#include "types/LgsFloat.h"

class LgsFloatConst final : public LgsConstant {
public:
    float value;

    explicit LgsFloatConst(const float value) : LgsConstant(&LOGOS_FLOAT), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsFloatConst() override = default;
};

#endif //LGSFLOATCONST_H
