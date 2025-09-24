#pragma once
#include "LgsType.h"

class LgsSubType final : public LgsType {
public:
    std::string name;
    LgsType* subtype;

    LgsSubType(const std::string& name, LgsType* baseType) : name(name), subtype(baseType) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    Lgs_RTType getRTType() override;
    std::string strFormatPart() const override;
    json::value asJSON() override;
};