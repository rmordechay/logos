#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isPrimitive = true;
        isInt = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    LgsExpr* addConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* subConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* mulConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* divConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* modConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* powConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* bitAndConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* bitOrConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* bitXorConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* lshiftConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* rshiftConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* eqConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* neConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* ltConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* gtConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* geConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* leConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* andConst(LgsExpr* left, LgsExpr* right) override;
    LgsExpr* orConst(LgsExpr* left, LgsExpr* right) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* powIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* ltIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* gtIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* geIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* leIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* andIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* orIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    std::string strFormatPart() const override;
    std::string getName() override;
    DIBasicType* getDebugType(LgsLLVMGen& cg) override;
};

inline LgsInt LGS_INT;
