#pragma once
#include "LgsType.h"

class LgsEnum final : public LgsType {
public:
    std::string name;

    explicit LgsEnum(const std::string& enumName) : name(enumName) {}
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
    size_t getSizeBytes() override;
    ~LgsEnum() override = default;
};


