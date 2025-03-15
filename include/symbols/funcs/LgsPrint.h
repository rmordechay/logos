#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "LgsBuiltinFunc.h"
#include "types/LgsFloat.h"
#include "types/LgsInt.h"
#include <types/LgsStr.h>
#include <types/LgsVoid.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    const string logosName = "print";
    const string IRNameInt = "print_Void_Int";
    const string IRNameString = "print_Void_Str";
    const string IRNameFloat = "print_Void_Float";
    FunctionType* const funcTypeInt = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    FunctionType* const funcTypeString = FunctionType::get(LOGOS_VOID.IRType, LOGOS_STRING.IRType, false);
    FunctionType* const funcTypeFloat = FunctionType::get(LOGOS_VOID.IRType, LOGOS_FLOAT.IRType, false);

    explicit LgsPrint() : LgsBuiltinFunc(logosName, &LOGOS_VOID) {}
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
    ~LgsPrint() override = default;
};

inline LgsPrint LOGOS_PRINT;

#endif //LOGOSPRINT_H
