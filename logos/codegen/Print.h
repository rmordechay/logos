#ifndef FUNCCALL_H
#define FUNCCALL_H
#include "CodeNode.h"
#include "exprs/LogosFuncCallExpr.h"

class Print final : public CodeNode {
public:
    LogosFuncCallExpr* funcCallExpr;

    explicit Print(LogosFuncCallExpr* func) : funcCallExpr(func) {}
    void generateCode(IRBuilder<>& builder, Module* module, std::map<std::string, Function*>* functions, map<string, Value*>* symbolTable) override;
};

#endif //FUNCCALL_H
