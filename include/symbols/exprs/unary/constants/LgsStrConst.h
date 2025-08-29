#pragma once
#include "LgsIntConst.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsStrConst final : public LgsUnaryExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const std::string& value) : value(value) {
        const auto lgsStr = new LgsStr();
        lgsStr->sizeExpr = new LgsIntConst(&LGS_INT, value.size());
        type = lgsStr;
    }

    std::string pname() override;
    Value* hash(LgsLLVMGen& cg) override;
    json::value asJSON() override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* other) override;
    LgsExpr* clone() override;
    LgsExpr* castTo(LgsType* toType) override;
    ~LgsStrConst() override;
};
