#pragma once
#include "types/iterables/LgsMap.h"

class LgsPair final : public LgsExpr {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsPair(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    void setDebugValue(LgsCgModule& cg) override;
    std::string asText() override;
};

class LgsHashMap final : public LgsExpr {
public:
    std::vector<LgsPair*> elements;

    LgsHashMap() = default;
    explicit LgsHashMap(LgsMap* mapType) : LgsExpr(mapType) {}
    void castImplicitly(LgsType* toType) override;
    void setDebugValue(LgsCgModule& cg) override;
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    ~LgsHashMap() override;
};

