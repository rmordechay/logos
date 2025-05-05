#ifndef LGSMAP_H
#define LGSMAP_H
#include "LgsIterable.h"
#include "LgsPair.h"
#include "LgsType.h"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsPair types;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsIterable(&types) {
        types.key = keyType;
        types.value = valueType;
    }
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    const string getName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsMap() override = default;
};

#endif //LGSMAP_H
