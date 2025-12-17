#pragma once
#include "LgsType.h"
#include "primitives/LgsFloat.h"
#include "primitives/LgsInt.h"

class LgsComplex final : public LgsType {
public:
    static constexpr auto name = "Complex";
    LgsType* realType;
    LgsType* imaginaryType;

    explicit LgsComplex(LgsType* realType = &LGS_FLOAT, LgsType* imaginaryType = &LGS_FLOAT): realType(realType), imaginaryType(imaginaryType) {
        passByRef = true;
    }
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string getName() override;
    ~LgsComplex() override;
};

inline LgsComplex LGS_COMPLEX;