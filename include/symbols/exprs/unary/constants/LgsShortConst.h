#ifndef LGSSHORTCONST_H
#define LGSSHORTCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsShort.h"

class LgsShortConst final : public LgsConstExpr {
public:
    int value;

    explicit LgsShortConst(const int value) : LgsConstExpr(&LGS_SHORT), value(value) {}
    string prettyName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    LgsExpr* convertExpr(LgsType* other) override;
    LgsExpr* clone() override;
    ~LgsShortConst() override = default;
};


#endif //LGSSHORTCONST_H
