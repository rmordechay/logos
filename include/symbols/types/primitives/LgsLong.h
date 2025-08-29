#pragma once
#include "LgsType.h"
#include "../codegen/LgsLLVMGen.h"


class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isPrimitive = true;
        isNumber = true;
        isInt = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    bool canCastTo(LgsType* other) override;
};

inline LgsLong LGS_LONG;


