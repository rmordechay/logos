#pragma once
#include "LgsType.h"

class LgsEnum final : public LgsType {
public:
    std::string name;

    explicit LgsEnum(const std::string& enumName) : name(enumName) {}
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string prettyName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
    size_t getSizeBytes() override;
    ~LgsEnum() override = default;
};


