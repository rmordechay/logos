#pragma once
#include "exprs/LgsExpr.h"

#define FOR_I_NAME "for.i"
#define FOR_IS_FIRST_NAME "for.isFirst"
#define FOR_IS_LAST_NAME "for.isLast"

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

    explicit LgsMetaVar(const std::string& name, const LgsMetaVarType forType) : name(name), varType(forType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsMetaVar* cloneExpr() override;
    std::string asText() override;
};

