#ifndef LGSBOOL_H
#define LGSBOOL_H
#include "LgsConstant.h"
#include "types/LgsBool.h"

class LgsBoolConst final : public LgsConstant {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsConstant(&LOGOS_BOOL), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsBoolConst() override = default;
};

#endif //LGSBOOL_H
