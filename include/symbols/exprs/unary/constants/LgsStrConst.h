#pragma once
#include "LgsConstExpr.h"
#include "LgsIntConst.h"
#include "types/LgsStr.h"

class LgsStrConst final : public LgsConstExpr {
public:
    string value;
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : LgsConstExpr(new LgsStr()), value(value) {
        type->asStr()->isStatic = true;
        type->asStr()->sizeExpr = new LgsIntConst(value.size());
    }

    Value* createIRValue(LgsRuntime* runtime) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};
