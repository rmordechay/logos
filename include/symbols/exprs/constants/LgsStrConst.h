#pragma once
#include "LgsIntConst.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsStrConst final : public LgsExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const std::string& value) : value(value) {
        const auto lgsStr = new LgsStr();
        lgsStr->sizeExpr = new LgsIntConst(&LGS_INT, value.size());
        type = lgsStr;
    }

    Value* loadIR(LgsLLVMGen& cg) override;
    std::string pname() override;
    Value* hash(LgsLLVMGen& cg) override;
    json::value asJSON() override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* other) override;
    LgsExpr* clone() override;
    LgsExpr* castTo(LgsType* toType) override;
    ~LgsStrConst() override;
};
