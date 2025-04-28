#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConstExpr.h"
#include "types/LgsInt.h"

class LgsIntConst final : public LgsConstExpr {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConstExpr(new LgsInt()), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsExpr* add(LgsExpr* other) override;
    LgsExpr* castStatically(LgsType* other) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* neIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* gtIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* ltIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* geIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* leIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
