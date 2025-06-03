#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsInt.h"

class LgsIntConst final : public LgsConstExpr {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConstExpr(&LGS_INT), value(value) {}
    string prettyName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    LgsExpr* convertExpr(LgsType* other) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* neIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* gtIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* ltIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* geIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* leIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* andIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* orIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitAndIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitOrIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitXorIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* rshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* lshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
