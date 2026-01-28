#pragma once
#include "LgsType.h"

class LgsComplex final : public LgsType {
public:
    static constexpr auto name = "Complex";
    LgsType* realType;
    LgsType* imaginaryType;

    explicit LgsComplex(LgsType* realType, LgsType* imaginaryType): realType(realType), imaginaryType(imaginaryType) {
        passByRef = true;
    }
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string getName() override;
    ~LgsComplex() override;
};
