#pragma once

#include "../types/iterables/LgsMap.h"

class LgsHashMap final : public LgsExpr {
public:
    std::vector<LgsMapEntry*> initialElements;

    explicit LgsHashMap(LgsMap* mapType) : LgsExpr(mapType) {
        mapType->isHeapAlloc = true;
    }
    explicit LgsHashMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsHashMap(new LgsMap(keyType, valueType)) {}
    std::string pname() override;
    json::value asJSON() override;
    ~LgsHashMap() override;
};

class LgsMapEntry final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapEntry(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    ~LgsMapEntry();
};


