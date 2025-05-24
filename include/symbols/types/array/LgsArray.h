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
        unpackLength = 1;
    }
    void inferArrayType(const vector<LgsExpr*>& exprs);
    int getDims() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    LgsType* createInnerType(size_t indexRange, LgsIndex* index) const override;
    bool canIndexTo(LgsType* indexType) override;
    void unpackTypes(const vector<LgsVarDec*>& varDecs) override;
    Value* getLength(CodeGenMetadata* metadata, Value* iter) override;
    Value* getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* iPtr) override;
    ~LgsArray() override;
};

#endif //LGSSARRAYTYPE_H
