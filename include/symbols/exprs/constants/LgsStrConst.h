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
        lgsStr->isStatic = true;
        lgsStr->size = new LgsIntConst(&LGS_INT, value.size());
        type = lgsStr;
    }

    Value* loadIR(LgsLLVMGen& cg) override;
    std::string getName() override;
    Value* hash(LgsLLVMGen& cg) override;
    json::value asJsonStr() override;
    ~LgsStrConst() override;
};
