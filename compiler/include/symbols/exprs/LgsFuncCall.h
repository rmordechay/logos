#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"

class LgsFuncType;
struct LgsSymbol;

struct LgsFuncArg {
    std::string name = "";
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    explicit LgsFuncArg(LgsExpr* expr, const std::string& name = "", const bool isSelf = false) : name(name), expr(expr), isSelf(isSelf) {}
};

class LgsFuncCall final : public LgsExpr {
public:
    std::string name;
    std::vector<LgsFuncArg> args;
    LgsFunc* func = nullptr;
    LgsFunc* coroutine = nullptr;
    bool inSelection = false;
    bool isNamed = false;
    bool isMock = false;
    LgsExpr* parentPtr = nullptr;
    LgsSymbol ref;

    explicit LgsFuncCall(const std::string& name) : name(name) {}
    std::string getGenericName() const;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* loadIR(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    bool equals(LgsFuncType* funcType) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaults(LgsFuncType* funcType) const;
    std::string asText() override;
    void setDebugValue(LgsLLVMGen& cg) override;
    LgsFuncCall* clone() override;
    ~LgsFuncCall() override;
};
