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
    LgsExpr* castExplicitly(LgsType* toType) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* hashValue(LgsLLVMGen& cg) override;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    std::string asText() override;
    void setDebugValue(LgsLLVMGen& cg) override;
    LgsVariable* clone() override;
};