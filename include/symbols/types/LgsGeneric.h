#pragma once
#include "LgsType.h"

class LgsGeneric final : public LgsType {
public:
    std::string name;

    explicit LgsGeneric(const std::string& name): name(name) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_rttype getRTType() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
};
