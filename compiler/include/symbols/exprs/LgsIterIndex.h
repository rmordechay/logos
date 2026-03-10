#pragma once
#include <string>

#include "exprs/LgsExpr.h"
#include "LgsValue.h"

class LgsStr;
class LgsMap;
class LgsDArray;
class LgsCodeGen;
namespace llvm {
class Value;
}

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
    LgsExpr* clone() const override;
    ~LgsIterIndex() override;
};
