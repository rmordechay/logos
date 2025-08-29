#pragma once
#include "LgsAssignable.h"
#include "LgsUnaryExpr.h"

class LgsStr;
class LgsMap;
class LgsDArray;
struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* loadFromDArray(LgsLLVMGen& cg, const LgsDArray* arr) const;
    Value* loadFromMap(LgsLLVMGen& cg, const LgsMap* map) const;
    Value* loadFromStr(LgsLLVMGen& cg, const LgsStr* str) const;
    Value* loadFromVec(LgsLLVMGen& cg) const;
    Value* loadFromSArray(LgsLLVMGen& cg) const;
    Value* createStrSlice(LgsLLVMGen& cg, const LgsStr* str) const;
    Value* getStrGEP(LgsLLVMGen& cg) const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    void assignScalar(LgsLLVMGen& cg, LgsExpr* expr);
    void assignArray(LgsLLVMGen& cg, const LgsArrayExpr* arr) const;
    void assignHashMap(LgsLLVMGen& cg, LgsHashMap* map);
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


