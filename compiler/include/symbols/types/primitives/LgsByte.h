#pragma once
#include "LgsType.h"

class LgsByte final : public LgsType {
public:
    static constexpr auto name = "Byte";

    LgsByte() {
        isInt = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsByte LGS_BYTE;