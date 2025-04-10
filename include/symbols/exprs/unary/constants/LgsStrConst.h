#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsConstExpr.h"
#include "types/LgsStr.h"
#include "exprs/unary/LgsIterable.h"
#include <string>

class LgsStrConst final : public LgsIterable, public LgsConstExpr {
public:
    string value;
    FunctionType* const cmpStrIRFuncType = FunctionType::get(i1Ty, {ptrTy, ptrTy}, false);

    explicit LgsStrConst(const string& value) : LgsConstExpr(new LgsStr()), value(value) {
        setFields(type);
    }
    size_t length() override;
    LgsExpr* add(LgsExpr* other) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* sizeIR(CodeGenMetadata* metadata) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    json asJson() override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H
