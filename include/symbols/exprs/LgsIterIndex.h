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

    explicit LgsIterIndex(LgsExpr* baseExpr, const LgsIndex index) : baseExpr(baseExpr), index(index) {
        isMutable = true;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* getIRPtrTo(LgsLLVMGen& cg) override;
    Value* loadFromDArray(LgsLLVMGen& cg);
    Value* loadFromMap(LgsLLVMGen& cg);
    Value* loadFromStr(LgsLLVMGen& cg) const;
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
