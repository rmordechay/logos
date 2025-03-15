#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "LgsBuiltinFunc.h"
#include "types/LgsChar.h"
#include "types/LgsFloat.h"
#include "types/LgsInt.h"
#include <types/LgsStr.h>
#include <types/LgsVoid.h>

struct FuncOverload {
    string name;
    FunctionType* const IRFuncType;
    vector<LgsParam> const params;
};

class LgsPrint final : public LgsBuiltinFunc {
public:
    const string logosName = "print";
    const string IRNameInt = "print_Void_Int";
    const string IRNameString = "print_Void_Str";
    const string IRNameFloat = "print_Void_Float";
    const string IRNameChar = "print_Void_Char";
    const LgsParam overloads[][] = {{LgsParam("str", &LOGOS_INT)}, {LgsParam("str", &LOGOS_STR)}};
    FunctionType* const funcTypeInt = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    FunctionType* const funcTypeFloat = FunctionType::get(LOGOS_VOID.IRType, LOGOS_FLOAT.IRType, false);
    FunctionType* const funcTypeString = FunctionType::get(LOGOS_VOID.IRType, LOGOS_STR.IRType, false);
    FunctionType* const funcTypeChar = FunctionType::get(LOGOS_VOID.IRType, LOGOS_CHAR.IRType, false);

    explicit LgsPrint() : LgsBuiltinFunc(logosName, &LOGOS_VOID) {}
    void setIRNames() override;
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
    string buildFuncName() const;
    ~LgsPrint() override = default;
};

inline LgsPrint LOGOS_PRINT;

#endif //LOGOSPRINT_H
