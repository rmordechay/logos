#ifndef LGSBOOL_H
#define LGSBOOL_H
#include "LgsConstExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsConstExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsConstExpr(&LGS_BOOL), value(value) {}
    string getValueAsString() const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* andIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* neIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* ltIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* gtIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* geIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* leIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* orIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};

#endif //LGSBOOL_H
