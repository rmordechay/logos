#pragma once
#include "LgsType.h"

class LgsSubType final : public LgsType {
public:
    std::string name;
    LgsType* subtype;
    bool isWeakType = false;

    LgsSubType(const std::string& name, LgsType* baseType) : name(name), subtype(baseType) {}
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};