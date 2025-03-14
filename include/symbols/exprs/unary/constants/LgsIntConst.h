#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConstant.h"
#include "types/LgsInt.h"

class LgsIntConst final : public LgsConstant {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConstant(&LOGOS_INT), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* add(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* sub(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* mul(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* div(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
