#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H

#include "LogosBuiltinFunc.h"
#include "LogosFunc.h"
#include "types/LogosInt.h"
#include <types/LogosString.h>
#include <types/LogosVoid.h>


class LogosPrint final : public LogosBuiltinFunc {
public:
    const string logosName = "print";
    const string IRNameInt = "printInt";
    const string IRNameString = "printString";
    FunctionType* const funcTypeInt = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    FunctionType* const funcTypeString = FunctionType::get(LOGOS_VOID.IRType, LOGOS_STRING.IRType, false);

    explicit LogosPrint() : LogosBuiltinFunc(logosName, &LOGOS_VOID) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    ~LogosPrint() override = default;
};

inline LogosPrint LOGOS_PRINT;

#endif //LOGOSPRINT_H
