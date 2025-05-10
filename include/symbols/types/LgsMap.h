#ifndef LGSMAP_H
#define LGSMAP_H
#include "LgsIterable.h"
#include "LgsPair.h"
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
        addMethod(&len);
    }
    void setUnderlyingType(const vector<LgsMapPair*>& exprs);
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    LgsType* getUnderlyingType() override;
    bool equals(LgsType* other) override;
    bool isIndexable(LgsType* indexType) override;
    LgsType* inferBinaryType(LgsType* other) override;
    Value* IRLength(CodeGenMetadata* metadata) override;
    ~LgsMap() override = default;
};

#endif //LGSMAP_H
