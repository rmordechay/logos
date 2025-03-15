#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "types/LgsChar.h"
#include "types/LgsFloat.h"
#include "types/LgsInt.h"
#include <types/LgsStr.h>
#include <types/LgsVoid.h>

class LgsPrint final : public LgsFunc {
public:
    const string IRNameInt = "print_Void_Int";
    const string IRNameString = "print_Void_Str";
    const string IRNameFloat = "print_Void_Float";
    const string IRNameChar = "print_Void_Char";
    FunctionType* const funcTypeInt = FunctionType::get(LOGOS_VOID.IRType, LOGOS_INT.IRType, false);
    FunctionType* const funcTypeFloat = FunctionType::get(LOGOS_VOID.IRType, LOGOS_FLOAT.IRType, false);
    FunctionType* const funcTypeString = FunctionType::get(LOGOS_VOID.IRType, LOGOS_STR.IRType, false);
    FunctionType* const funcTypeChar = FunctionType::get(LOGOS_VOID.IRType, LOGOS_CHAR.IRType, false);

    explicit LgsPrint(const vector<LgsParam*>& params) : LgsFunc("print", &LOGOS_VOID, params) {}
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
    string buildFuncName() const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsPrint() override = default;
};

#endif //LOGOSPRINT_H
