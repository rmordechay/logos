#pragma once
#include "LgsType.h"

class LgsGenericType final : public LgsType {
public:
    std::string name;
    LgsType* bounds = nullptr;

    explicit LgsGenericType(const std::string& name): name(name) {}
    Type* getIRType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    void replaceGenerics(std::unordered_map<std::string, LgsType*>& replacements) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};
