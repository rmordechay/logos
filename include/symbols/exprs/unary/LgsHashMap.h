#ifndef LGSHASHMAP_H
#define LGSHASHMAP_H
#include "LgsUnaryExpr.h"
#include "types/LgsMap.h"

class LgsMapPair final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapPair(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    ~LgsMapPair() = default;
};

class LgsHashMap final : public LgsUnaryExpr {
public:
    LgsMap mapType;
    vector<LgsMapPair*> initialElements;

    explicit LgsHashMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        type = &mapType;
        mapType.kvType.key = keyType;
        mapType.kvType.value = valueType;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsHashMap() override = default;
};

#endif //LGSHASHMAP_H
