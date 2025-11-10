#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsLong.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    LgsStr(): LgsIterable(&LGS_CHAR) {
        passByRef = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    LgsFunc* getLenFunc() override;
    LgsFunc* getIsEmptyFunc() override;
    LgsFunc* getIsNotEmptyFunc() override;
    std::string strFormatPart() const override;
    LgsExpr* addConst(LgsExpr* self, LgsExpr* other) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    LgsType* clone() override;
};
