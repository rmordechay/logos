#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H

#include "types/LogosInt.h"
#include <types/LogosVoid.h>
#include <types/LogosString.h>
#include "LogosFunc.h"


class LogosPrint final : public LogosFunc {
public:
    const string logosName = "print";
    const string IRNameInt = "printInt";
    const string IRNamePrint = "printString";
    FunctionType* const funcTypeInt = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    FunctionType* const funcTypeString = FunctionType::get(LOGOS_VOID.IRType, LOGOS_STRING.IRType, false);

    explicit LogosPrint() : LogosFunc(logosName, &LOGOS_VOID) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    ~LogosPrint() override = default;
};

#endif //LOGOSPRINT_H
