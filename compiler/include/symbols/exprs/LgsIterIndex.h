#pragma once
#include "codegen/LgsCgModule.h"
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
        index.from = from;
        index.to = to;
    }
    Value* loadIR(LgsCodeGen& cg) override;
    LgsExpr* getBaseExpr() const;
    void setIRElementPtr(LgsCodeGen& cg, bool assign = false);
    void setIRRangePtr(LgsCodeGen& cg, bool assign = false);
    void assign(LgsCodeGen& cg, LgsExpr* right) override;
    std::string asText() override;
    Type* getSArrayType(LgsCodeGen& cg) const;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* clone() override;
    ~LgsIterIndex() override;
};
