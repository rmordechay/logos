#pragma once
#include "LgsType.h"

class LgsGenericType final : public LgsType {
public:
    std::string name;

    explicit LgsGenericType(const std::string& name): name(name) {}
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    LgsType* clone() override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    bool canReplace(LgsType* type);
};
