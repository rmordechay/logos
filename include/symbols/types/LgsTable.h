#pragma once
#include "LgsType.h"

class LgsTable final : public LgsType {
public:
    static constexpr auto name = "Table";

    std::string pname() override;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
    json::value asJSON() override;
};
