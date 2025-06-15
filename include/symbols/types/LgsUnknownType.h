#pragma once
#include "LgsType.h"


class LgsUnknownType final : public LgsType {
public:
    static constexpr auto typeName = "Unknown";
    string name;

    LgsUnknownType() = default;
    explicit LgsUnknownType(const string& name) : name(name) {}
    Type* getIRType() override;
    string getIRName() override;
    string pName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsUnknownType() override = default;
};


