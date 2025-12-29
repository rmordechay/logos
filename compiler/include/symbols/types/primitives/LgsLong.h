#pragma once
#include "LgsType.h"
#include "codegen/LgsCgModule.h"

class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isPrimitive = true;
        isInt = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee) override;
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
    std::string fmtStr() const override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsLong LGS_LONG;


