#ifndef LGSENUM_H
#define LGSENUM_H
#include "LgsType.h"

class LgsEnumField;

class LgsEnum final : public LgsType {
public:
    string name;

    LgsEnum() = default;
    explicit LgsEnum(const string& name) : name(name) {}
    Type* getIRType() override;
    string getIRName() override;
    nlohmann::json asJSON() const override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsEnum() override = default;
};

#endif //LGSENUM_H
