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
    LgsArrayLenFunc len{this};
    LgsArrayDeleteFunc delete_{this};

    explicit LgsArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        addMethod(&add);
        addMethod(&len);
    }
    void inferArrayType(const vector<LgsExpr*>& exprs);
    int getDims() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    LgsType* createInnerType(size_t indexRange) const override;
    bool canIndexTo(LgsType* indexType) override;
    ~LgsArray() override;
};

#endif //LGSSARRAYTYPE_H
