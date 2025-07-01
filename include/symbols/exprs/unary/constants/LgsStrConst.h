#pragma once
#include "LgsIntConst.h"
#include "types/LgsStr.h"

class LgsStrConst final : public LgsUnaryExpr {
public:
    string value;
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : value(value) {
        const auto lgsStr = new LgsStr();
        lgsStr->sizeExpr = new LgsIntConst(value.size());
        lgsStr->iterLen = value.size();
        type = lgsStr;
    }

    Value* hashValue(LgsModule* runtime) override;
    Value* createIRValue(LgsModule* runtime) override;
    Value* eqIR(LgsModule* runtime, LgsExpr* other) override;
    Value* addIR(LgsModule* runtime, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};
