#pragma once
#include "LgsType.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isPrimitive = true;
        isInt = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* ltIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* gtIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* geIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* leIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* andIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* orIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string strFormatPart() const override;
    size_t sizeBytes() override;
    bool canCastTo(LgsType* other) override;
};

inline LgsBool LGS_BOOL;


