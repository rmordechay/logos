#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "LogosBuiltinFunc.h"
#include "types/LogosInt.h"
#include <types/LogosString.h>
#include <types/LogosVoid.h>

class LogosPrint final : public LogosBuiltinFunc {
public:
    const string logosName = "print";
    const string IRNameInt = "print_Void_Int";
    const string IRNameString = "print_Void_Str";
    FunctionType* const funcTypeInt = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    FunctionType* const funcTypeString = FunctionType::get(LOGOS_VOID.IRType, LOGOS_STRING.IRType, false);

    explicit LogosPrint() : LogosBuiltinFunc(logosName, &LOGOS_VOID) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    ~LogosPrint() override = default;
};

inline LogosPrint LOGOS_PRINT;

#endif //LOGOSPRINT_H
