#pragma once
#include "LgsType.h"
#include <string>

class LgsEnumField : public LgsType {
public:
    std::string name;
    LgsEnum* parentType;

    LgsEnumField(LgsEnum* parentType, const std::string& name) : name(name), parentType(parentType) {
        rtt = RTT_ENUM;
    }
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCgModule& cg, Value* v) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};
