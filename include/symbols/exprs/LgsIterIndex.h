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
    LgsExpr* getBaseExpr() const;
    void setIRElementPtr(LgsLLVMGen& cg, bool inAssignment = false);
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    void assignScalar(LgsLLVMGen& cg, LgsExpr* expr) const;
    std::string asText() override;
    Type* getSArrayType(LgsLLVMGen& cg) const;
    ~LgsIterIndex() override;
};
