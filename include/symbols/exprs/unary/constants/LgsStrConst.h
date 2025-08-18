#pragma once
#include "LgsNumberConst.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsStrConst final : public LgsUnaryExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const std::string& value) : value(value) {
        const auto lgsStr = new LgsStr();
        lgsStr->sizeExpr = new LgsNumberConst(&LGS_INT, value.size());
        type = lgsStr;
    }

    std::string pname() override;
    Value* hash(LgsCodeGen* codeGen) override;
    void createIRValue(LgsCodeGen* codeGen) override;
    Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    ~LgsStrConst() override;
};
