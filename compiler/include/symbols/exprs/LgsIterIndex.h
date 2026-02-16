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
        index.from = from;
        index.to = to;
    }

    Value* getIRRangePtr(LgsCodeGen& cg) const;
    LgsExpr* getBaseExpr() const;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* clone() override;
    ~LgsIterIndex() override;
};
