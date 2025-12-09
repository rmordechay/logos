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
    Value* lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* other) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    size_t sizeBytes() override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsBool LGS_BOOL;


