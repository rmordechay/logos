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
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* getBaseExpr() const;
    void setIRElementPtr(LgsLLVMGen& cg, bool assign = false);
    void setIRRangePtr(LgsLLVMGen& cg, bool assign = false);
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    void assignScalar(LgsLLVMGen& cg, LgsExpr* expr) const;
    std::string asText() override;
    Type* getSArrayType(LgsLLVMGen& cg) const;
    ~LgsIterIndex() override;
};
