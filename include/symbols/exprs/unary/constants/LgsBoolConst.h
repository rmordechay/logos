#ifndef LGSBOOL_H
#define LGSBOOL_H
#include "LgsConstExpr.h"
#include "types/LgsBool.h"

class LgsBoolConst final : public LgsConstExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsConstExpr(new LgsBool()), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* andIR(CodeGenMetadata* metadata, LgsExpr* right) override;
    ~LgsBoolConst() override = default;
};

#endif //LGSBOOL_H
