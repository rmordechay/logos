#ifndef LGSSARRAYTYPE_H
#define LGSSARRAYTYPE_H
#include "LgsType.h"
#include "LgsIterable.h"

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";

    explicit LgsArray(LgsType* underlyingType = nullptr): LgsIterable(underlyingType) {}
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    const string getName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool isIndexable(LgsType* indexType) override;
    ~LgsArray() override = default;
};

#endif //LGSSARRAYTYPE_H
