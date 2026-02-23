#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_INT;
    }
    std::string getName() override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    LgsExpr* getZeroValue() override;
    void asIRText(LgsStrBuilder& sb, Value* ptr) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
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
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsInt LGS_INT;
