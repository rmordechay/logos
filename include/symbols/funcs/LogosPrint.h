#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H

#include "LogosFunc.h"
#include "types/LogosInt.h"

#include <types/LogosVoid.h>

class LogosPrint final : public LogosFunc {
public:
    LogosVarDec* params[2] = {
        new LogosVarDec("input", &LOGOS_INT),
        new LogosVarDec("count", &LOGOS_INT)
    };

    explicit LogosPrint() : LogosFunc("print", &LOGOS_VOID) {}
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    FunctionCallee getFuncCallee(CodeGenMetadata* metadata) override;
    vector<Value*> getArgs(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    ~LogosPrint() override = default;
};

inline LogosPrint logosPrint;

#endif //LOGOSPRINT_H
