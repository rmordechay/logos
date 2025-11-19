#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsSize.h"
#include <iostream>

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const int64_t value) : LgsExpr(type), value(value) {
        isMutable = false;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void hashNode(size_t& oldHash) override;
    Value* hashValue(LgsLLVMGen& cg) override;
    void setDebugValue(LgsLLVMGen& cg) override;
    LgsIntConst* clone() override;
};
