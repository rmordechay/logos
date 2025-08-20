#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsMap.h"

class LgsHashMap final : public LgsUnaryExpr {
public:
    std::vector<LgsMapEntry*> initialElements;

    explicit LgsHashMap(LgsMap* mapType) : LgsUnaryExpr(mapType) {}
    explicit LgsHashMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsHashMap(new LgsMap(keyType, valueType)) {}
    std::string pname() override;
    void createIRValue(LgsCodeGen* codeGen) override;
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


