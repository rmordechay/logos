#pragma once
#include "exprs/LgsExpr.h"

class LgsStr;
class LgsMap;
class LgsDArray;

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};

class LgsIterIndex final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsIndex index;

    explicit LgsIterIndex(LgsExpr* baseExpr, LgsExpr* from = nullptr, LgsExpr* to = nullptr) : baseExpr(baseExpr) {
        isMutable = true;
        index.from = from;
        index.to = to;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    void setIRElementPtr(LgsLLVMGen& cg);
    Value* loadFromDArray(LgsLLVMGen& cg);
    Value* loadFromMap(LgsLLVMGen& cg);
    Value* loadFromStr(LgsLLVMGen& cg);
    Value* loadFromVec(LgsLLVMGen& cg) const;
    Value* loadFromSArray(LgsLLVMGen& cg) const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    void assignScalar(LgsLLVMGen& cg, LgsExpr* expr);
    void assignArray(LgsLLVMGen& cg, const LgsArrayExpr* arr) const;
    void assignHashMap(LgsLLVMGen& cg, LgsHashMap* map);
    std::string pname() override;
    json::value asJSON() override;
    ~LgsIterIndex() override;
};
