#pragma once
#include "LgsUnaryExpr.h"
#include <LgsValue.h>

class LgsMap;
class LgsArray;
struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* getGEP(LgsRuntime* runtime) const;
    Value* getIRFromDynArray(LgsRuntime* runtime, LgsArray* arr) const;
    Value* getIRFromMap(LgsRuntime* runtime, LgsMap* map) const;
    Value* getIRFromStr(LgsRuntime* runtime) const;
    void storeHashMap(LgsRuntime* runtime, LgsHashMap* hashMap) const;
    void storeScalar(LgsRuntime* runtime, LgsExpr* value);
    void storeArray(LgsRuntime* runtime, const LgsArrayExpr* arr) const;
    std::string getName() override;
    std::string prettyName() override;
    static void setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices);
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};


