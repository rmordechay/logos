#ifndef LGSMAP_H
#define LGSMAP_H
#include "types/LgsIterable.h"
#include "types/LgsPair.h"
#include "LgsMapMethods.h"
#include "funcs/LgsMethodImpl.h"

class LgsMapPair;

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsPair kvType;
    LgsMapNewFunc new_{this};
    LgsMapGetFunc get{this};
    LgsMapAddFunc add{this};
    LgsMapDeleteFunc delete_{this};
    LgsMapLenFunc len{this};

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsIterable(&kvType) {
        kvType.key = keyType;
        kvType.value = valueType;
        unpackLength = 2;
        addMethod(&len);
    }
    void setBaseType(const vector<LgsMapPair*>& exprs);
    int getDims() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    LgsType* getBaseType() override;
    bool equals(LgsType* other) override;
    bool canIndexTo(LgsType* indexType) override;
    LgsType* inferBinaryType(LgsType* other) override;
    LgsType* createInnerType(size_t indexRange, LgsIndex* index) const override;
    void unpackTypes(const vector<LgsVarDec*>& varDecs) override;
    ~LgsMap() override = default;
};

#endif //LGSMAP_H
