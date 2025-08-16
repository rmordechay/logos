#pragma once
#include "LgsIntConst.h"
#include "types/LgsStr.h"

class LgsStrConst final : public LgsUnaryExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const std::string& value) : value(value) {
        const auto lgsStr = new LgsStr();
        lgsStr->sizeExpr = new LgsIntConst(value.size());
        lgsStr->initialLength = value.size();
        type = lgsStr;
    }

    std::string pname() override;
    Value* hashValue(LgsCodeGen* codeGen) override;
    void createIRValue(LgsCodeGen* codeGen) override;
    Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    ~LgsStrConst() override;
};
