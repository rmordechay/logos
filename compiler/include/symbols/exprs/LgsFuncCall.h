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
    std::vector<LgsType*> genericArgs;
    LgsFunc* func = nullptr;
    LgsFunc* coroutine = nullptr;
    bool inSelection = false;
    bool isDeferred = false;
    bool isNamed = false;
    bool isMock = false;
    LgsSymbol ref;

    explicit LgsFuncCall(const std::string& name) : name(name) {}
    bool equals(LgsExpr* other) override;
    bool equals(LgsFuncType* funcType) const;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsFuncCall* clone() override;
    ~LgsFuncCall() override;
};
