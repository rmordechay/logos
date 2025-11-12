#pragma once
#include "types/iterables/LgsMap.h"

class LgsHashMap final : public LgsExpr {
public:
    std::vector<LgsPair> pairs;

    LgsHashMap() = default;
    explicit LgsHashMap(LgsMap* mapType) : LgsExpr(mapType) {}
    void completeType(LgsType* toType) override;
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    ~LgsHashMap() override;
};



