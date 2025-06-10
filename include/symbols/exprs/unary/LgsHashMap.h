#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsMap.h"

class LgsHashMap final : public LgsUnaryExpr {
public:
    LgsMap* map = nullptr;
    vector<LgsMapEntry*> initialElements;

    explicit LgsHashMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        map = new LgsMap(keyType, valueType);
        type = map;
    }
    explicit LgsHashMap(LgsMap* mapType) : LgsUnaryExpr(mapType), map(mapType) {}
    void initIRMap(LgsRuntime* runtime);
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsHashMap() override = default;
};

class LgsMapEntry final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapEntry(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    ~LgsMapEntry() = default;
};


