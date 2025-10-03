#pragma once
#include "funcs/LgsFunc.h"
#include "types/primitives/LgsInt.h"
#include "LgsIterable.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";

    explicit LgsSArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        isStatic = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string strFormatPart() const override;
    LgsType* applyOp(LgsOperator op, LgsType* other) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    json::value asJsonStr() override;
};
