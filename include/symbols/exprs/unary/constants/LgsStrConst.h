#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsCharConst.h"
#include "LgsConstExpr.h"
#include "types/LgsStr.h"
#include "../../../types/LgsIterable.h"
#include <string>

class LgsStrConst final : public LgsConstExpr {
public:
    string value;
    FunctionType* const cmpStrIRFuncType = FunctionType::get(i1Ty, {ptrTy, ptrTy}, false);

    explicit LgsStrConst(const string& value) : LgsConstExpr(&LGS_STR), value(value) {}
    bool isIterable() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
