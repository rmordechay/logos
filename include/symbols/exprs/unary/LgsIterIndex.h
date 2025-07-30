#pragma once
#include "LgsUnaryExpr.h"
#include <LgsValue.h>

class LgsMap;
class LgsDArray;
struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    Value* createIRValue(LgsCodeGen* codeGen) override;
    Value* getArrGEP(LgsCodeGen* codeGen) const;
    Value* getIRFromArray(LgsCodeGen* codeGen, LgsDArray* arr) const;
    Value* getIRFromMap(LgsCodeGen* codeGen, LgsMap* map) const;
    Value* getIRFromStr(LgsCodeGen* codeGen, const LgsStr* str) const;
    Value* getStrSlice(LgsCodeGen* codeGen, const LgsStr* str) const;
    Value* getStrGEP(LgsCodeGen* codeGen) const;
    string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};


