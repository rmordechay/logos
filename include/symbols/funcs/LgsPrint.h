#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "LgsBuiltinFunc.h"
#include "types/LgsInt.h"
#include <types/LgsString.h>
#include <types/LgsVoid.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    const string logosName = "print";
    const string IRNameInt = "print_Void_Int";
    const string IRNameString = "print_Void_Str";
    FunctionType* const funcTypeInt = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    FunctionType* const funcTypeString = FunctionType::get(LOGOS_VOID.IRType, LOGOS_STRING.IRType, false);

    explicit LgsPrint() : LgsBuiltinFunc(logosName, &LOGOS_VOID) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    ~LgsPrint() override = default;
};

inline LgsPrint LOGOS_PRINT;

#endif //LOGOSPRINT_H
