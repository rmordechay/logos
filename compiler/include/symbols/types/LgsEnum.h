#pragma once
#include "LgsType.h"

class LgsEnum : public LgsType {
public:
    std::string name;
    LgsType* exprType = nullptr;

    explicit LgsEnum(const std::string& name) : name(name) {
        rttKind = RTT_ENUM;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    size_t sizeBytes() override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsEnum() override;
};

