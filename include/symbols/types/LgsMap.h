#ifndef LGSMAP_H
#define LGSMAP_H
#include "LgsIterable.h"
#include "LgsPair.h"
#include "LgsType.h"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsPair underlyingType;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsIterable(&underlyingType) {
        underlyingType.key = keyType;
        underlyingType.value = valueType;
    }
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    const string getName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool isIndexable(LgsType* indexType) override;
    LgsType* getUnderlyingType() override;
    ~LgsMap() override = default;
};

#endif //LGSMAP_H
