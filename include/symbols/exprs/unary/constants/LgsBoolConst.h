#ifndef LGSBOOL_H
#define LGSBOOL_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsConstExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsConstExpr(&LGS_BOOL), value(value) {}
    string getValueAsString() const;
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* andIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* neIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* ltIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* gtIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* geIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* leIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* orIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitAndIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitOrIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitXorIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* rshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* lshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};

#endif //LGSBOOL_H
