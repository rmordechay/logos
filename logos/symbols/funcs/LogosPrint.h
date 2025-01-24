#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "LogosFunc.h"

#include <types/LogosVoid.h>

class LogosPrint final : public LogosFunc {
public:
    LogosVarDec* params[1] = {new LogosVarDec("input", &LOGOS_INT)};

    LogosPrint() : LogosFunc("print", &LOGOS_VOID) {}
    Function* getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) override;
    ~LogosPrint() override = default;
};

inline LogosPrint logosPrint;

#endif //LOGOSPRINT_H
