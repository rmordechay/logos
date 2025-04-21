#ifndef LGSENUM_H
#define LGSENUM_H
#include "LgsType.h"
#include "exprs/unary/LgsUnaryExpr.h"

class LgsEnumField;

class LgsEnum final : public LgsType {
public:
    string name;

    LgsEnum() = default;
    explicit LgsEnum(const string& name) : name(name) {}
    size_t size() override;
    Type* getIRType() override;
    json asJSON() const override;
    const string getName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsEnum() override = default;
};

#endif //LGSENUM_H
