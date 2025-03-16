#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConst.h"
#include "types/LgsInt.h"

class LgsIntConst final : public LgsConst {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConst(&LOGOS_INT), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsExpr* add(LgsExpr* other) override;
    json asJson() override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
