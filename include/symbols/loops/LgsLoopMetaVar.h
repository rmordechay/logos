#pragma once
#include "exprs/LgsExpr.h"

#define FOR_I_NAME "for.i"
#define FOR_IS_FIRST_NAME "for.isFirst"
#define FOR_IS_LAST_NAME "for.isLast"

enum LgsLoopMetaVarType {
    FOR_I,
    FOR_IS_FIRST,
    FOR_IS_LAST,
};

class LgsLoopMetaVar final : public LgsExpr {
public:
    LgsLoopMetaVarType varType;

    explicit LgsLoopMetaVar(const LgsLoopMetaVarType forType) : varType(forType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string pname() override;
    json::value asJSON() override;
};

