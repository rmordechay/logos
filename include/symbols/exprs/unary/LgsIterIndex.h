#pragma once
#include "LgsUnaryExpr.h"

class LgsMap;
class LgsDArray;
struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {
        isAssignable = true;
    }

    Value* loadFromDArray(LgsLLVM& codeGen, const LgsDArray* arr) const;
    Value* loadFromMap(LgsLLVM& codeGen, const LgsMap* map) const;
    Value* loadFromStr(LgsLLVM& codeGen, const LgsStr* str) const;
    Value* loadFromVec(LgsLLVM& codeGen) const;
    Value* createStrSlice(LgsLLVM& codeGen, const LgsStr* str) const;
    Value* loadFromSArray(LgsLLVM& codeGen) const;
    Value* getStrGEP(LgsLLVM& codeGen) const;
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


