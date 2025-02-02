#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H

#include "LogosFunc.h"

#include <types/LogosVoid.h>


class LogosPrint final : public LogosFunc {
public:
    LogosVarDec* params[2] = {
        new LogosVarDec("input", &LOGOS_INT),
        new LogosVarDec("count", &LOGOS_INT)
    };

    explicit LogosPrint() : LogosFunc("print", &LOGOS_VOID) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) override;
    FunctionCallee getFuncCallee(IRBuilder<>* builder, LogosStack* theStack, Module* module) override;
    vector<Value*> getArgs(IRBuilder<>* builder, LogosStack* theStack, Module* module, const vector<LogosExpr*>& args) override;
    ~LogosPrint() override = default;
};

inline LogosPrint logosPrint;

#endif //LOGOSPRINT_H
