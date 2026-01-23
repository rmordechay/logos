#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isInt = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* modIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* powIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* bitAndIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* bitOrIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* bitXorIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* rshiftIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* lshiftIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCgModule& cg, Value* v) override;
    std::string getName() override;
    LgsType* clone() override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsInt LGS_INT;
inline LgsInt LGS_IMAGINARY;
