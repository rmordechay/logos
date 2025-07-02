#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsMap.h"

class LgsHashMap final : public LgsUnaryExpr {
public:
    vector<LgsMapEntry*> initialElements;

    explicit LgsHashMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        type = new LgsMap(keyType, valueType);
    }
    explicit LgsHashMap(LgsMap* mapType) : LgsUnaryExpr(mapType) {}
    void initIRMap(LgsModule* module);
    Value* createIRValue(LgsModule* module) override;
    ~LgsHashMap() override = default;
};

class LgsMapEntry final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapEntry(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    ~LgsMapEntry() = default;
};


