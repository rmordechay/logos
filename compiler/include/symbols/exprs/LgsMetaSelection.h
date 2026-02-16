#pragma once
#include "LgsExpr.h"

class LgsMetaSelection final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsExpr* child;

    LgsMetaSelection(LgsExpr* baseExpr, LgsExpr* expr): baseExpr(baseExpr), child(expr) {}
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
};
