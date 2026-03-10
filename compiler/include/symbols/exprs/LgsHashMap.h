#pragma once
#include <string>
#include <vector>

#include "LgsExpr.h"
#include "types/iterables/LgsMap.h"

class LgsPair final : public LgsExpr {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsPair(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
};

class LgsHashMap final : public LgsExpr {
public:
    std::vector<LgsPair*> elements;

    LgsHashMap() = default;
    explicit LgsHashMap(LgsMap* mapType) : LgsExpr(mapType) {}
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
    ~LgsHashMap() override;
};

