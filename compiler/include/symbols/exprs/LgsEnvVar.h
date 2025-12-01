#pragma once
#include "LgsExpr.h"
#include "types/iterables/LgsStr.h"

class LgsEnvVar final : public LgsExpr {
public:
    std::string name;

    explicit LgsEnvVar(const std::string& name) : LgsExpr(new LgsStr()), name(name) {}
    std::string asText() override;
    Value* loadIR(LgsCgModule& cg) override;
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCgModule& cg) override;
};
