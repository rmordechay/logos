#ifndef LGSBOOL_H
#define LGSBOOL_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsConstExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsConstExpr(&LGS_BOOL), value(value) {}
    string getValueAsString() const;
    Value* createIRValue(CodegenMetadata* metadata) override;
    Value* andIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* eqIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* neIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* ltIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* gtIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* geIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* leIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* orIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitAndIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitOrIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitXorIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* rshiftIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* lshiftIR(CodegenMetadata* metadata, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};

#endif //LGSBOOL_H
