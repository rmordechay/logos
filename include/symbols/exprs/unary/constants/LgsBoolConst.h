#ifndef LGSBOOL_H
#define LGSBOOL_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsConstExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsConstExpr(&LGS_BOOL), value(value) {}
    string getValueAsString() const;
    Value* createIRValue(Module* module) override;
    Value* andIR(Module* module, LgsExpr* other) override;
    Value* eqIR(Module* module, LgsExpr* other) override;
    Value* neIR(Module* module, LgsExpr* other) override;
    Value* ltIR(Module* module, LgsExpr* other) override;
    Value* gtIR(Module* module, LgsExpr* other) override;
    Value* geIR(Module* module, LgsExpr* other) override;
    Value* leIR(Module* module, LgsExpr* other) override;
    Value* orIR(Module* module, LgsExpr* other) override;
    Value* bitAndIR(Module* module, LgsExpr* other) override;
    Value* bitOrIR(Module* module, LgsExpr* other) override;
    Value* bitXorIR(Module* module, LgsExpr* other) override;
    Value* rshiftIR(Module* module, LgsExpr* other) override;
    Value* lshiftIR(Module* module, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};

#endif //LGSBOOL_H
