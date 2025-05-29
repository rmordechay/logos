#ifndef LGSSARRAYTYPE_H
#define LGSSARRAYTYPE_H
#include "LgsArrayMethods.h"
#include "types/LgsType.h"
#include "types/LgsIterable.h"

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";
    LgsArrayInitFunc init{this};
    LgsArrayGetFunc get{this};
    LgsArrayPutFunc put{this};
    LgsArrayAddFunc add{this};
    LgsArrayLenFunc len{this};
    LgsArrayFreeFunc free{this};
    LgsArrayDeleteFunc delete_{this};

    explicit LgsArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        addMethod(&add);
        addMethod(&len);
        unpackLength = 1;
    }
    StructType* getIRStructType() const;
    void inferArrayType(const vector<LgsExpr*>& exprs);
    size_t getSize() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    void unpackTypes(const vector<LgsVarDec*>& varDecs) override;
    Value* getLength(CodeGenMetadata* metadata, Value* iterValue) override;
    Value* getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* indexPtr) override;
    LgsType* clone() override;
    ~LgsArray() override;
};

#endif //LGSSARRAYTYPE_H
