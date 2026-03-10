#pragma once
#include <string>

#include "LgsExpr.h"

struct LgsSymbolTable;

class LgsModuleExpr final : public LgsExpr {
public:
    std::string name;
    LgsSymbolTable* moduleGlobals = nullptr;

    explicit LgsModuleExpr(const std::string& name) : name(name) {}
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
};
