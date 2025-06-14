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
    Value* getArrGEP(LgsRuntime* runtime) const;
    Value* getIRFromArray(LgsRuntime* runtime, LgsArray* arr) const;
    Value* getIRFromMap(LgsRuntime* runtime, LgsMap* map) const;
    Value* getIRFromStr(LgsRuntime* runtime, LgsStr* str) const;
    Value* getStrSlice(const LgsRuntime* runtime, LgsStr* str) const;
    Value* getStrGEP(LgsRuntime* runtime) const;
    string getName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};


