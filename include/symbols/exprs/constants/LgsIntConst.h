#pragma once
#include "exprs/LgsExpr.h"

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const size_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* castTo(LgsType* toType, bool explicitCast = false) override;
    Value* eqIR(LgsLLVMGen& cg, Value* other) override;
    Value* neIR(LgsLLVMGen& cg, Value* other) override;
    Value* ltIR(LgsLLVMGen& cg, Value* other) override;
    Value* gtIR(LgsLLVMGen& cg, Value* other) override;
    Value* geIR(LgsLLVMGen& cg, Value* other) override;
    Value* leIR(LgsLLVMGen& cg, Value* other) override;
    Value* andIR(LgsLLVMGen& cg, Value* other) override;
    Value* orIR(LgsLLVMGen& cg, Value* other) override;
    std::string getName() override;
    LgsExpr* clone() override;
    json::value asJsonStr() override;
};
