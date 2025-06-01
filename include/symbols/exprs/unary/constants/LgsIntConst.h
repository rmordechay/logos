#ifndef LGSINTCONST_H
#define LGSINTCONST_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsInt.h"

class LgsIntConst final : public LgsConstExpr {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsConstExpr(&LGS_INT), value(value) {}
    string prettyName() override;
    Value* createIRValue(CodegenMetadata* metadata) override;
    LgsExpr* convertExpr(LgsType* other) override;
    Value* eqIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* neIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* gtIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* ltIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* geIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* leIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* andIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* orIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitAndIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitOrIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitXorIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* rshiftIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* lshiftIR(CodegenMetadata* metadata, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
