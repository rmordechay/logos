#pragma once
#include "LgsType.h"

class LgsPtr final : public LgsType {
public:
    static constexpr auto name = "CPtr";
    LgsType* baseType;

    explicit LgsPtr(LgsType* baseType) : baseType(baseType) {
        rtt = baseType->rtt;

    }
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    ~LgsPtr() override;
};
