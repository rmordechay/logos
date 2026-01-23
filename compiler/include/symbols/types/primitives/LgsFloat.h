#pragma once
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isFloat = true;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCodeGen& cg, Value* v) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    LgsType* clone() override;
};

inline LgsFloat LGS_FLOAT;
