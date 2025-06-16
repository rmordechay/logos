#pragma once
#include "LgsIntConst.h"
#include "types/LgsStr.h"

class LgsStrConst final : public LgsUnaryExpr {
public:
    string value;
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : value(value) {
        const auto lgsStr = new LgsStr();
        lgsStr->isStatic = true;
        lgsStr->sizeExpr = new LgsIntConst(value.size());
        lgsStr->iterLen = value.size();
        lgsStr->isStatic = true;
        type = lgsStr;
    }

    Value* createIRValue(LgsRuntime* runtime) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};
