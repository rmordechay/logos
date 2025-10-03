#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsLong.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    LgsStr(): LgsIterable(&LGS_CHAR) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    json::value asJsonStr() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    LgsType* applyOp(LgsOperator op, LgsType* other) override;
    Value* addIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    LgsFunc* getLenFunc() override;
    LgsFunc* getIsEmptyFunc() override;
    LgsFunc* getIsNotEmptyFunc() override;
    std::string strFormatPart() const override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    bool canCastTo(LgsType* other) override;
};
