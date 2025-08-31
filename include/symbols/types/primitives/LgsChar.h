#pragma once
#include "LgsType.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
        rtt = RTT_CHAR;
    }
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
};

inline LgsChar LGS_CHAR;


