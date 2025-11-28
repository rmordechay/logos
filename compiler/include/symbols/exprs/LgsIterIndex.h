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

    explicit LgsIterIndex(LgsExpr* baseExpr, LgsExpr* from = nullptr, LgsExpr* to = nullptr) : baseExpr(baseExpr) {
        index.from = from;
        index.to = to;
    }
    Value* loadIR(LgsCgModule& cg) override;
    LgsExpr* getBaseExpr() const;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    void setIRElementPtr(LgsCgModule& cg, bool assign = false);
    void setIRRangePtr(LgsCgModule& cg, bool assign = false);
    void assign(LgsCgModule& cg, LgsExpr* expr) override;
    void assignScalar(LgsCgModule& cg, LgsExpr* expr) const;
    std::string asText() override;
    Type* getSArrayType(LgsCgModule& cg) const;
    ~LgsIterIndex() override;
};
