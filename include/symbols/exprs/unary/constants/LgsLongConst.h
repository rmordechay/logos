#ifndef LGSLONGCONST_H
#define LGSLONGCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsLong.h"


class LgsLongConst final : public LgsConstExpr {
public:
    long value;

    explicit LgsLongConst(const int value) : LgsConstExpr(&LGS_LONG), value(value) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    LgsExpr* convertExpr(LgsType* other) override;
    ~LgsLongConst() override = default;
};



#endif //LGSLONGCONST_H
