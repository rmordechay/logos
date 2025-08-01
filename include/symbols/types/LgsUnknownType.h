#pragma once
#include "LgsType.h"

class LgsUnknownType final : public LgsType {
public:
    string name;
    constexpr static auto genricName = "<Unknown>";

    explicit LgsUnknownType(const string& name = "") : name(name) {
        isUnknown = true;
    }
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    bool equals(LgsType* other) override;
    ~LgsUnknownType() override = default;
};
