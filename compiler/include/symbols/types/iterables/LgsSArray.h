#pragma once
#include "LgsIterable.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";

    explicit LgsSArray(LgsType* baseType, LgsExpr* size): LgsIterable(baseType, size) {
        isStatic = true;
        passByRef = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsLLVMGen& cg) override;
    std::string strFormatPart() const override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    Value* lenIR(LgsLLVMGen& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
};
