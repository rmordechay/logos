#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConstant.h"
#include "types/LgsInt.h"

class LgsIntConst final : public LgsConstant {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConstant(&LOGOS_INT), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* operator+(LgsExpr* other) override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
