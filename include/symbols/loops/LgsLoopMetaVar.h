#pragma once
#include "exprs/LgsExpr.h"

enum LgsLoopMetaVarType {
    FOR_I,
    FOR_IS_FIRST,
    FOR_IS_LAST,
    FOR_PREV,
    FOR_NEXT,
};

class LgsLoopMetaVar final : public LgsExpr {
public:
    LgsLoopMetaVarType varType;
    LgsForLoop* forLoop = nullptr;

    explicit LgsLoopMetaVar(const LgsLoopMetaVarType forType) : varType(forType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string getName() override;
    json::value asJsonStr() override;
};

