#pragma once
#include "types/iterables/LgsMap.h"

class LgsHashMap final : public LgsExpr {
public:
    std::vector<LgsPair> elements;

    LgsHashMap() = default;
    explicit LgsHashMap(LgsMap* mapType) : LgsExpr(mapType) {}
    void castImplicitly(LgsType* toType) override;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    ~LgsHashMap() override;
};



