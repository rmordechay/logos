#pragma once
#include "LgsType.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isPrimitive = true;
        isNumber = true;
        isInt = true;
    }
    std::string pname() override;
    json::value asJSON() override;
    llvm::Type* getIRType(LgsCodeGen& codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    size_t getSizeBytes() override;
    bool canCastTo(LgsType* other) override;
};

inline LgsBool LGS_BOOL;


