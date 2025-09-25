#pragma once
#include "LgsType.h"

class LgsUInt final : public LgsType {
public:
    static constexpr auto name = "UInt";

    LgsUInt() {
        isUnsigned = true;
        isPrimitive = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
};

inline LgsUInt LGS_UINT;