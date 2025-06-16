#pragma once
#include "LgsObject.h"

class LgsInterface final : public LgsObject {
public:
    string interfaceName;

    explicit LgsInterface(const string& name) : LgsObject(name), interfaceName(name) {}
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    ~LgsInterface() override = default;
};
