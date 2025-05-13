#ifndef LGSSARRAYTYPE_H
#define LGSSARRAYTYPE_H
#include "LgsArrayMethods.h"
#include "types/LgsType.h"
#include "types/LgsIterable.h"

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";
    LgsArrayNewFunc new_{this};
    LgsArrayGetFunc get{this};
    LgsArrayAddFunc add{this};
    LgsArrayDeleteFunc delete_{this};
    LgsArrayLenFunc len{this};

    explicit LgsArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        addMethod(&add);
    }
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    void setBaseType(const vector<LgsExpr*>& exprs);
    bool isIndexable(LgsType* indexType) override;
    ~LgsArray() override = default;
};

#endif //LGSSARRAYTYPE_H
