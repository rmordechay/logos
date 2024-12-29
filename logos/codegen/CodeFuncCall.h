#ifndef CODEFUNCCALL_H
#define CODEFUNCCALL_H
#include "LogosCodeNode.h"
#include "LogosType.h"
#include "exprs/LogosExpr.h"
#include "funcs/LogosFunc.h"


class CodeFuncCall final : public LogosCodeNode {
public:
    std::shared_ptr<LogosFunc> func;
    std::vector<std::shared_ptr<LogosType>> args;

    explicit CodeFuncCall(const std::shared_ptr<LogosFunc>& func) : func(func) {}
    void generateCode(const LLVMContext& context, const IRBuilder<>& builder, Module* module) override;
};

#endif //CODEFUNCCALL_H
