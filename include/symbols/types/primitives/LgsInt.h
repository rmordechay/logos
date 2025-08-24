#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isPrimitive = true;
        isNumber = true;
        isInt = true;
    }
    size_t getSizeBytes() override;
    llvm::Type* getIRType(LgsLLVM& codeGen) override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsType* clone() override;
    llvm::DIBasicType* getDebugType(LgsLLVM& codeGen) override;
};

inline LgsInt LGS_INT;
