#pragma once
#include "LgsIntConst.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsStrConst final : public LgsExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> parts;

    explicit LgsStrConst(const std::string& value) : value(value) {
        isValueKnown = true;
        const auto lgsStr = new LgsStr();
        lgsStr->isStatic = true;
        lgsStr->size = new LgsIntConst(&LGS_INT, value.size());
        setType(lgsStr);
    }
    LgsExpr* castTo(LgsType* toType, bool explicitCast) override;
    Value* castToIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
    Value* hash(LgsLLVMGen& cg) override;
    ~LgsStrConst() override;
};
