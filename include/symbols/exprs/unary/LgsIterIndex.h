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
    Value* createIRValue(LgsModule* runtime) override;
    Value* getArrGEP(LgsModule* runtime) const;
    Value* getIRFromArray(LgsModule* runtime, LgsArray* arr) const;
    Value* getIRFromMap(LgsModule* runtime, LgsMap* map) const;
    Value* getIRFromStr(LgsModule* runtime, LgsStr* str) const;
    Value* getStrSlice(LgsModule* runtime, const LgsStr* str) const;
    Value* getStrGEP(LgsModule* runtime) const;
    string getExprName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};


