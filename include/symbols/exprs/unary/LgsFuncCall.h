#pragma once
#include "LgsUnaryExpr.h"

class LgsFuncType;
struct LgsSymbol;

class LgsFuncCall final : public LgsUnaryExpr {
public:
    std::string name;
    std::vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    bool isMethodCall = false;
    LgsSymbol* callback = nullptr;

    explicit LgsFuncCall(const std::string& name, const std::vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
    json::value asJSON() override;
    Value* getCallback(LgsCodeGen* codeGen) const;
    bool equals(const LgsFuncType* funcType) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaultParams(const LgsFuncType* funcType) const;
    void resolveVirtualFunc(LgsCodeGen* codeGen) const;
    ~LgsFuncCall() override;
};
