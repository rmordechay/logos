#pragma once
#include "LgsType.h"

class LgsDouble final : public LgsType {
public:
    static constexpr auto name = "Double";

    LgsDouble() {
        isFloat = true;
        isPrimitive = true;
        rttKind = RTT_DOUBLE;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsDouble LGS_DOUBLE;