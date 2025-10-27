#pragma once
#include "LgsType.h"

class LgsGeneric final : public LgsType {
public:
    std::string name;

    explicit LgsGeneric(const std::string& name): name(name) {
        isGeneric = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    LgsType* clone() override;
    std::string strFormatPart() const override;
};
