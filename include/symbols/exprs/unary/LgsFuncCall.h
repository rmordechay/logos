#pragma once
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncType;
struct LgsSymbol;

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    std::string name;
    std::vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    bool isMethodCall = false;
    LgsSymbol* callback = nullptr;

    explicit LgsFuncCall(const std::string& name, const std::vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    Value* getCallback(LgsCodeGen* codeGen) const;
    void createIRStmt(LgsCodeGen* codeGen) override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    bool equals(const LgsFuncType* funcType) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaultParams(const LgsFuncType* funcType) const;
    void resolveVirtualFunc(LgsCodeGen* codeGen) const;
    std::string prettyName() override;
    std::string format(std::string& indentStr) override;
    ~LgsFuncCall() override = default;
};
