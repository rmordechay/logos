#pragma once
#include "LgsType.h"

class LgsSelf final : public LgsType {
public:
    std::string name;
    LgsType* baseType = nullptr;

    explicit LgsSelf(const std::string& name) : name(name) {}
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
};
