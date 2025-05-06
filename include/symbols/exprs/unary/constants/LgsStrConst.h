#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsConstExpr.h"
#include "types/LgsStr.h"
#include <string>

class LgsStrConst final : public LgsConstExpr {
public:
    LgsStr strType;
    string value;
    FunctionType* const cmpStrIRFuncType = FunctionType::get(i1Ty, {ptrTy, ptrTy}, false);

    explicit LgsStrConst(const string& value) : LgsConstExpr(&strType), value(value) {
        strType.isStatic = true;
        strType.sizes = {value.size()};
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
