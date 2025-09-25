#pragma once
#include "LgsType.h"

class LgsSize final : public LgsType {
public:
    static constexpr auto name = "Size";

    LgsSize() {
        isPrimitive = true;
        isInt = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
};

inline LgsSize LGS_SIZE;