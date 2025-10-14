#pragma once
#include "exprs/LgsExpr.h"

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const size_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* castTo(LgsType* toType, bool explicitCast = false) override;
    Value* castToIR(LgsLLVMGen& cg, LgsType* toType) override;
    void parseAsJSON(std::stringstream& json) override;
    std::string getName() override;
    Value* hash(LgsLLVMGen& cg) override;
    LgsExpr* clone() override;
};
