#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const int64_t value) : LgsExpr(type), value(value) {}
    explicit LgsIntConst(const int64_t value) : LgsExpr(&LGS_INT), value(value) {}
    Value* loadIR(LgsCodeGen& cg) override;
    LgsExpr* cast(LgsType* toType, bool explicitly) override;
    LgsIntConst* clone() override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCodeGen& cg) override;
};
