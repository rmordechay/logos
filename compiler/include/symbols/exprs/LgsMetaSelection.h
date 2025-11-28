#pragma once
#include "LgsExpr.h"

class LgsMetaSelection final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsExpr* child;

    LgsMetaSelection(LgsExpr* baseExpr, LgsExpr* expr): baseExpr(baseExpr), child(expr) {}
    Value* loadIR(LgsCgModule& cg) override;
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCgModule& cg) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    std::string asText() override;
};
