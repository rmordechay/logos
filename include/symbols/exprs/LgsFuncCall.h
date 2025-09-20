#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"


class LgsFuncType;
struct LgsSymbol;

class LgsFuncCall final : public LgsExpr {
public:
    std::string name;
    std::vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    bool isMethodCall = false;
    bool isCoroutine = false;
    LgsSymbol ref;

    explicit LgsFuncCall(const std::string& name, const std::vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    bool equals(LgsExpr* other) override;
    bool equals(const LgsFuncType* other) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaultParams(const LgsFuncType* funcType) const;
    void resolveVirtualFunc(LgsLLVMGen& cg) const;
    void completeType(LgsType* toType) override;
    std::string pname() override;
    json::value asJSON() override;
    ~LgsFuncCall() override;
};
