#pragma once
#include "LgsUnaryExpr.h"

class LgsMap;
class LgsDArray;
struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    Value* loadFromDArray(LgsCodeGen* codeGen, LgsDArray* arr) const;
    Value* loadFromMap(LgsCodeGen* codeGen, LgsMap* map) const;
    Value* loadFromStr(LgsCodeGen* codeGen, const LgsStr* str) const;
    Value* loadFromVec(LgsCodeGen* codeGen) const;
    Value* createStrSlice(LgsCodeGen* codeGen, const LgsStr* str) const;
    Value* loadFromSArray(LgsCodeGen* codeGen) const;
    Value* getStrGEP(LgsCodeGen* codeGen) const;
    std::string pname() override;
    json::value asJSON() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;

    ~LgsIndex() {
        if (from) {
            delete from;
            from = nullptr;
        }
        if (to) {
            delete to;
            to = nullptr;
        }
    }
};


