#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H

#include "LogosFunc.h"
#include "types/LogosInt.h"

#include <types/LogosVoid.h>

class LogosPrint final : public LogosFunc {
public:
    const string IRName = "printInt";
    const string logosName = "print";
    const LogosVarDec* params[2] = {
        new LogosVarDec("input", &LOGOS_INT),
        new LogosVarDec("count", &LOGOS_INT)
    };

    explicit LogosPrint() : LogosFunc(logosName, &LOGOS_VOID) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    ~LogosPrint() override = default;
};

inline LogosPrint logosPrint;

#endif //LOGOSPRINT_H
