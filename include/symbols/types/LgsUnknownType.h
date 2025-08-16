#pragma once
#include <utility>
#include "LgsType.h"

class LgsUnknownType final : public LgsType {
public:
    std::string name;

    explicit LgsUnknownType(std::string  name) : name(std::move(name)) {}
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string prettyName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    bool equals(LgsType* other) override;
    ~LgsUnknownType() override = default;
};
