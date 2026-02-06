#pragma once
#include "LgsExpr.h"

class LgsMetaSelection final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsExpr* child;

    LgsMetaSelection(LgsExpr* baseExpr, LgsExpr* expr): baseExpr(baseExpr), child(expr) {}
    Value* loadIR(LgsCodeGen& cg) override;
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    std::string asText() override;
};
