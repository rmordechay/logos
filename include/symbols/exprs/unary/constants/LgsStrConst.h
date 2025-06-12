#pragma once
#include "LgsIntConst.h"
#include "types/LgsStr.h"

class LgsStrConst final : public LgsUnaryExpr {
public:
    string value;
    LgsStr* strType = new LgsStr();
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : value(value) {
        strType->isConst = true;
        strType->isStatic = true;
        strType->sizeExpr = new LgsIntConst(value.size());
        strType->iterLen = value.size();
        type = strType;
    }

    Value* createIRValue(LgsRuntime* runtime) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};
