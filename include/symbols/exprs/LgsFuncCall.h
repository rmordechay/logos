#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"


class LgsFuncType;
struct LgsSymbol;

class LgsFuncCall final : public LgsExpr {
public:
    std::string name;
    std::vector<LgsExpr*> args;
    std::vector<LgsType*> generics;
    LgsFunc* func = nullptr;
    bool isMethodCall = false;
    bool isCoroutine = false;
    bool isDeferred = false;
    LgsExpr* selfPtr = nullptr;
    LgsSymbol ref;

    explicit LgsFuncCall(const std::string& name, const std::vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    bool equals(const LgsFuncType* other) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    std::string asText() override;
    void setDebugValue(LgsLLVMGen& cg) override;
    LgsStmt* cloneStmt() override;
    ~LgsFuncCall() override;
};
