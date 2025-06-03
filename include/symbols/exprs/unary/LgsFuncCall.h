#ifndef LOGOSFUNCCALL_H
#define LOGOSFUNCCALL_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncType;
struct LgsSymbol;

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    std::string name;
    std::vector<LgsExpr*> args;
    LgsSymbol* callback = nullptr;
    LgsFunc* func = nullptr;

    explicit LgsFuncCall(const std::string& name, const std::vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    Value* call(LgsRuntime* runtime) const;
    Value* getCallback(LgsRuntime* runtime) const;
    bool equalsRaw(const LgsFuncType* funcType) const;
    bool equals(const LgsFuncType* funcType) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaultParams(const LgsFuncType* funcType) const;
    Value* resolveVirtualFunc(LgsRuntime* runtime) const;
    void createIRStmt(LgsRuntime* runtime) override;
    Value* createIRValue(LgsRuntime* runtime) override;
    std::string getName() override;
    std::string format(std::string& indentStr) override;
    std::string prettyName() override;
    ~LgsFuncCall() override = default;
};

#endif //LOGOSFUNCCALL_H