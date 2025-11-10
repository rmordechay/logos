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
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    LgsExpr* addConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* subConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* mulConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* divConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* modConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* bitAndConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* bitOrConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* bitXorConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* lshiftConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* rshiftConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* eqConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* neConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* ltConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* gtConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* geConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* leConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* andConst(LgsExpr* self, LgsExpr* other) override;
    LgsExpr* orConst(LgsExpr* self, LgsExpr* other) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string strFormatPart() const override;
    size_t getSizeBytes() override;
    bool canCastTo(LgsType* other) override;
};

inline LgsBool LGS_BOOL;


