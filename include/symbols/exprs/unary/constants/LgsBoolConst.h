#ifndef LGSBOOL_H
#define LGSBOOL_H
#include "LgsConst.h"
#include "types/LgsBool.h"

class LgsBoolConst final : public LgsConst {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsConst(&LOGOS_BOOL), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsBoolConst() override = default;
};

#endif //LGSBOOL_H
