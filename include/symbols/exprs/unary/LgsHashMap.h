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
    void initIRMap(LgsRuntime* runtime);
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsHashMap() override = default;
};

class LgsMapEntry final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapEntry(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    static StructType* getStructType();
    ~LgsMapEntry() = default;
};


