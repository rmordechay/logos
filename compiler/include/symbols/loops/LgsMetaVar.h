#pragma once
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

    explicit LgsMetaVar(const std::string& name, const LgsMetaVarType forType) : name(name), varType(forType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsMetaVar* clone() override;
    bool equals(LgsExpr* other) override;
    std::string asText() override;
};

