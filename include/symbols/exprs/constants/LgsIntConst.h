#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsSize.h"

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const size_t value) : LgsExpr(type), value(value) {
        isValueKnown = true;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* staticCast(LgsType* toType, bool explicitCast = false) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void hashNode(size_t& oldHash) override;
    Value* hashValue(LgsLLVMGen& cg) override;
    void setDebugValue(LgsLLVMGen& cg) override;
    LgsIntConst* clone() override;
};
