#pragma once
#include "LgsExpr.h"

struct LgsSymbolTable;

class LgsModuleExpr final : public LgsExpr {
public:
    std::string name;
    LgsSymbolTable* moduleTable = nullptr;

    explicit LgsModuleExpr(const std::string& name) : name(name) {}
    LgsExpr* cast(bool explicitly) override;
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
};
