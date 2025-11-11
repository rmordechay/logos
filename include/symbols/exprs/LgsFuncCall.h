#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"

class LgsFuncType;
struct LgsSymbol;

struct LgsFuncCallArg {
    std::string name = "";
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    LgsFuncCallArg(const std::string& name, LgsExpr* expr, const bool isSelf = false) : name(name), expr(expr), isSelf(isSelf) {}
};

class LgsFuncCall final : public LgsExpr {
public:
    std::string name;
    std::vector<LgsType*> generics;
    std::vector<LgsFuncCallArg> args;
    LgsFunc* func = nullptr;
    bool inSelection = false;
    bool isCoroutine = false;
    bool isDeferred = false;
    bool isNamed = false;
    LgsSymbol ref;

    explicit LgsFuncCall(const std::string& name) : name(name) {}
    std::string getGenericName() const;
    Value* castToIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* loadIR(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    bool equals(const LgsFuncType* funcType) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaults(const LgsFuncType* lgsFunc) const;
    std::string asText() override;
    void setDebugValue(LgsLLVMGen& cg) override;
    LgsStmt* cloneStmt() override;
    ~LgsFuncCall() override;
};
