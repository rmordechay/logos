#pragma once
#include "LgsType.h"

class LgsUInt final : public LgsType {
public:
    static constexpr auto name = "UInt";

    LgsUInt() {
        isNumber = true;
        isUnsigned = true;
        isPrimitive = true;
    }
    size_t getSizeBytes() override;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
};

inline LgsUInt LGS_UINT;