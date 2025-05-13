#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsInt.h"

class LgsIntConst final : public LgsConstExpr {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConstExpr(&LGS_INT), value(value) {}
    string getStrFormatPart() const override;
    string prettyName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsExpr* castStatically(LgsType* other) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* neIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* gtIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* ltIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* geIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* leIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* andIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* orIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
