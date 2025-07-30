#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsMap.h"

class LgsHashMap final : public LgsUnaryExpr {
public:
    vector<LgsMapEntry*> initialElements;

    explicit LgsHashMap(LgsMap* mapType) : LgsUnaryExpr(mapType) {
        isHeapAlloc = true;
    }
    explicit LgsHashMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsHashMap(new LgsMap(keyType, valueType)) {}
    string prettyName() override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    void free(LgsCodeGen* codeGen) override;
    ~LgsHashMap() override = default;
};

class LgsMapEntry final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapEntry(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    ~LgsMapEntry() = default;
};


