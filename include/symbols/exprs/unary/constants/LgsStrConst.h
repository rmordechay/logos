#pragma once
#include "LgsIntConst.h"
#include "types/LgsStr.h"

class LgsStrConst final : public LgsUnaryExpr {
public:
    string value;
    string formatedStr = "";
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : value(value) {
        const auto lgsStr = new LgsStr();
        lgsStr->sizeExpr = new LgsIntConst(value.size());
        lgsStr->initialLength = value.size();
        type = lgsStr;
    }

    string prettyName() override;
    Value* hashValue(LgsCodeGen* codeGen) override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    ~LgsStrConst() override;
};
