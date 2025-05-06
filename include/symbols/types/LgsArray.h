#ifndef LGSSARRAYTYPE_H
#define LGSSARRAYTYPE_H
#include "LgsArrayMethods.h"
#include "LgsType.h"
#include "LgsIterable.h"

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";
    LgsArrayNewFunc new_{this};
    LgsArrayGetFunc get{this};
    LgsArrayAddFunc add{this};
    LgsArrayDeleteFunc delete_{this};
    LgsArrayLenFunc len{this};

    explicit LgsArray(LgsType* underlyingType = nullptr): LgsIterable(underlyingType) {
        addMethod(&add);
    }
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool isIndexable(LgsType* indexType) override;
    ~LgsArray() override = default;
};

#endif //LGSSARRAYTYPE_H
