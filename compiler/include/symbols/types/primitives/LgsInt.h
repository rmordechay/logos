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
    Type* getIRType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* powIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    std::string fmtStr() const override;
    std::string getName() override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsInt LGS_INT;
inline LgsInt LGS_IMAGINARY;
