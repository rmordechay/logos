#pragma once
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isFloat = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCgModule& cg, Value* v) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    Value* divIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) override;
    DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* clone() override;
};

inline LgsFloat LGS_FLOAT;
