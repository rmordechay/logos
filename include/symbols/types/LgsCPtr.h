#pragma once
#include "LgsType.h"
#include "logos/LgsCodeGen.h"

class LgsCPtr final : public LgsType {
public:
    static constexpr auto name = "CPtr";
    LgsType* baseType;

    explicit LgsCPtr(LgsType* baseType) : baseType(baseType) {}
    std::string getName() override;
    std::string pname() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    ~LgsCPtr() override = default;
};
