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
    bool boundsChecked = false;

    explicit LgsIterIndex(LgsExpr* baseExpr, LgsExpr* from = nullptr, LgsExpr* to = nullptr) : baseExpr(baseExpr) {
        isMutable = true;
        index.from = from;
        index.to = to;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    void setIRElementPtr(LgsLLVMGen& cg);
    Value* loadFromSArray(LgsLLVMGen& cg) const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    void assignScalar(LgsLLVMGen& cg, LgsExpr* expr) const;
    void assignArray(LgsLLVMGen& cg, const LgsArrayExpr* arr) const;
    void assignHashMap(LgsLLVMGen& cg, LgsHashMap* map);
    std::string getName() override;
    json::value asJsonStr() override;
    ~LgsIterIndex() override;
};
