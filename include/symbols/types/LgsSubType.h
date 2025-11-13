#pragma once
#include "LgsType.h"

class LgsSubType final : public LgsType {
public:
    std::string name;
    LgsType* subtype;
    bool isWeakType = false;

    LgsSubType(const std::string& name, LgsType* baseType) : name(name), subtype(baseType) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    LgsSubType* clone() override;
};