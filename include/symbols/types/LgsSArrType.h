#ifndef LGSSARRAYTYPE_H
#define LGSSARRAYTYPE_H
#include "LgsType.h"
#include "LgsIterable.h"

class LgsSArrType final : public LgsIterable {
public:
    static constexpr auto name = "SArrayType";

    explicit LgsSArrType(LgsType* underlyingType, const vector<size_t>& arraySize) : LgsIterable(underlyingType, arraySize) {}
    Type* getIRType() override;
    Type* getUnderlyingIRType() override;
    LgsExpr* getZeroValue() override;
    const string getName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
};

#endif //LGSSARRAYTYPE_H
