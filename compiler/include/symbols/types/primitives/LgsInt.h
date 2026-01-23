#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isInt = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* bitAndIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* bitOrIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* bitXorIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* rshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* lshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCodeGen& cg, Value* v) override;
    std::string getName() override;
    LgsType* clone() override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsInt LGS_INT;
inline LgsInt LGS_IMAGINARY;
