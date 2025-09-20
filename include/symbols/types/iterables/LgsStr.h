#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsLong.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    LgsStr(): LgsIterable(&LGS_CHAR) {
        isSliceable = true;
        rtt = RTT_STR;
    }
    Type* getIRBaseType(LgsLLVMGen* cg) const;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    LgsFunc* getLenFunc() override;
    LgsFunc* getIsEmptyFunc() override;
    LgsFunc* getIsNotEmptyFunc() override;
    std::string strFormatPart() const override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsLLVMGen& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
};
