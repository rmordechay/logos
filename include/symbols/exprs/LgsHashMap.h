#pragma once
#include "types/iterables/LgsMap.h"

class LgsHashMap final : public LgsExpr {
public:
    std::vector<LgsMapEntry*> initialElements;

    LgsHashMap() = default;
    explicit LgsHashMap(LgsMap* mapType) : LgsExpr(mapType) {}
    void completeType(LgsType* toType) override;
    std::string pname() override;
    json::value asJsonStr() override;
    ~LgsHashMap() override;
};

class LgsMapEntry final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapEntry(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    ~LgsMapEntry();
};


