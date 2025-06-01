#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsInt.h"

class LgsIntConst final : public LgsConstExpr {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConstExpr(&LGS_INT), value(value) {}
    string prettyName() override;
    Value* createIRValue(Module* module) override;
    LgsExpr* convertExpr(LgsType* other) override;
    Value* eqIR(Module* module, LgsExpr* other) override;
    Value* neIR(Module* module, LgsExpr* other) override;
    Value* gtIR(Module* module, LgsExpr* other) override;
    Value* ltIR(Module* module, LgsExpr* other) override;
    Value* geIR(Module* module, LgsExpr* other) override;
    Value* leIR(Module* module, LgsExpr* other) override;
    Value* andIR(Module* module, LgsExpr* other) override;
    Value* orIR(Module* module, LgsExpr* other) override;
    Value* bitAndIR(Module* module, LgsExpr* other) override;
    Value* bitOrIR(Module* module, LgsExpr* other) override;
    Value* bitXorIR(Module* module, LgsExpr* other) override;
    Value* rshiftIR(Module* module, LgsExpr* other) override;
    Value* lshiftIR(Module* module, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
