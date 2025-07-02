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
    Value* createIRValue(LgsModule* module) override;
    Value* getArrGEP(LgsModule* module) const;
    Value* getIRFromArray(LgsModule* module, LgsArray* arr) const;
    Value* getIRFromMap(LgsModule* module, LgsMap* map) const;
    Value* getIRFromStr(LgsModule* module, LgsStr* str) const;
    Value* getStrSlice(LgsModule* module, const LgsStr* str) const;
    Value* getStrGEP(LgsModule* module) const;
    string getExprName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};


