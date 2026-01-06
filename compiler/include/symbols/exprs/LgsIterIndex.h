#pragma once
#include "codegen/LgsCodeGen.h"
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
    Value* loadIR(LgsCgModule& cg) override;
    LgsExpr* getBaseExpr() const;
    void setIRElementPtr(LgsCgModule& cg, bool assign = false);
    void setIRRangePtr(LgsCgModule& cg, bool assign = false);
    void assign(LgsCgModule& cg, LgsExpr* expr, Value* level) override;
    std::string asText() override;
    Type* getSArrayType(LgsCgModule& cg) const;
    void setDebugValue(LgsCgModule& cg) override;
    LgsExpr* clone() override;
    ~LgsIterIndex() override;
};
