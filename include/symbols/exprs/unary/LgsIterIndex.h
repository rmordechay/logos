#pragma once
#include "LgsAssignable.h"
#include "LgsUnaryExpr.h"

class LgsMap;
class LgsDArray;
struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr, public LgsAssignable {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    Value* loadIR(LgsLLVM& codeGen) override;
    Value* loadFromDArray(LgsLLVM& codeGen, const LgsDArray* arr) const;
    Value* loadFromMap(LgsLLVM& codeGen, const LgsMap* map) const;
    Value* loadFromStr(LgsLLVM& codeGen, const LgsStr* str) const;
    Value* loadFromVec(LgsLLVM& codeGen) const;
    Value* loadFromSArray(LgsLLVM& codeGen) const;
    Value* createStrSlice(LgsLLVM& codeGen, const LgsStr* str) const;
    Value* getStrGEP(LgsLLVM& codeGen) const;
    void assign(LgsLLVM& codeGen, LgsExpr* expr) override;
    void assignScalar(LgsLLVM& codeGen, LgsExpr* expr);
    void assignArray(LgsLLVM& codeGen, const LgsArrayExpr* arr) const;
    void assignHashMap(LgsLLVM& codeGen, LgsHashMap* map);
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


