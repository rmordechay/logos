#ifndef LGSHASHMAP_H
#define LGSHASHMAP_H
#include "LgsUnaryExpr.h"
#include "types/LgsMap.h"

class LgsHashMap final : public LgsUnaryExpr {
public:
    LgsMap mapType;
    vector<LgsMapPair*> initialElements;

    explicit LgsHashMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        setType(&mapType);
        mapType.kvType.key = keyType;
        mapType.kvType.value = valueType;
    }
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsHashMap() override = default;
};

class LgsMapPair final {
public:
    LgsExpr* key;
    LgsExpr* value;

    LgsMapPair(LgsExpr* key, LgsExpr* value) : key(key), value(value) {}
    ~LgsMapPair() = default;
};

#endif //LGSHASHMAP_H
