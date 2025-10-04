#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"
struct LgsSymbol;

class LgsVariable final : public LgsExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsExpr(type), name(name) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    Value* hash(LgsLLVMGen& cg) override;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    Value* eqIR(LgsLLVMGen& cg, Value* other) override;
    Value* neIR(LgsLLVMGen& cg, Value* other) override;
    Value* ltIR(LgsLLVMGen& cg, Value* other) override;
    Value* gtIR(LgsLLVMGen& cg, Value* other) override;
    Value* geIR(LgsLLVMGen& cg, Value* other) override;
    Value* leIR(LgsLLVMGen& cg, Value* other) override;
    Value* andIR(LgsLLVMGen& cg, Value* other) override;
    Value* orIR(LgsLLVMGen& cg, Value* other) override;
    std::string getName() override;
    json::value asJsonStr() override;
};