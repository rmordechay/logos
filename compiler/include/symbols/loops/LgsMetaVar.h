#pragma once
#include <string>

#include "exprs/LgsExpr.h"

enum LgsMetaVarType {
    FOR_I,
    FOR_ELEMENT,
    FOR_IS_FIRST,
    FOR_IS_LAST,
};

class LgsMetaVar final : public LgsExpr {
public:
    std::string name;
    LgsMetaVarType varType;

    explicit LgsMetaVar(const LgsMetaVarType forType) : LgsMetaVar("", forType) {}
    explicit LgsMetaVar(const std::string& name, const LgsMetaVarType forType) : name(name), varType(forType) {}
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* clone() override;
};

