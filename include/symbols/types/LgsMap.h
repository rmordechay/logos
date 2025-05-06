#ifndef LGSMAP_H
#define LGSMAP_H
#include "LgsIterable.h"
#include "LgsPair.h"
#include "LgsMapMethods.h"
#include "funcs/LgsMethodImpl.h"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsPair underlyingType;
    LgsMapGetFunc get{this};
    LgsMapAddFunc add{this};
    LgsMapDeleteFunc delete_{this};
    LgsMapLenFunc len{this};

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsIterable(&underlyingType) {
        underlyingType.key = keyType;
        underlyingType.value = valueType;
        addMethod(&len);
    }

    Value* IRLength(CodeGenMetadata* metadata) override;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool isIndexable(LgsType* indexType) override;
    LgsType* getUnderlyingType() override;
    ~LgsMap() override = default;
};

#endif //LGSMAP_H
