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
    Value* createIRFromArray(LgsCodeGen* codeGen, LgsDArray* arr) const;
    Value* createIRFromMap(LgsCodeGen* codeGen, LgsMap* map) const;
    Value* createIRFromStr(LgsCodeGen* codeGen, const LgsStr* str) const;
    Value* createStrSlice(LgsCodeGen* codeGen, const LgsStr* str) const;
    Value* getArrGEP(LgsCodeGen* codeGen) const;
    Value* getStrGEP(LgsCodeGen* codeGen) const;
    std::string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};


