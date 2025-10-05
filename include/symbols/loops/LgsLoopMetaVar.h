#pragma once
#include "exprs/LgsExpr.h"

#define FOR_I_NAME "for.i"
#define FOR_ELEMENT_NAME "for.element"
#define FOR_IS_FIRST_NAME "for.isFirst"
#define FOR_IS_LAST_NAME "for.isLast"
#define FOR_PREV_NAME "for.prev"
#define FOR_NEXT_NAME "for.next"

enum LgsLoopMetaVarType {
    FOR_I,
    FOR_ELEMENT,
    FOR_IS_FIRST,
    FOR_IS_LAST,
    FOR_PREV,
    FOR_NEXT,
};

class LgsLoopMetaVar final : public LgsExpr {
public:
    std::string name;
    LgsLoopMetaVarType varType;
    LgsForLoop* forLoop = nullptr;

    explicit LgsLoopMetaVar(const std::string& name, const LgsLoopMetaVarType forType) : name(name), varType(forType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string getName() override;
    json::value asJsonStr() override;
};

