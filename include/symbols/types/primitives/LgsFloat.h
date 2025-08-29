#pragma once
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isPrimitive = true;
        isNumber = true;
        isFloatPoint = true;
    }
    llvm::Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    std::string pname() override;
    json::value asJSON() override;
};

inline LgsFloat LGS_FLOAT;
