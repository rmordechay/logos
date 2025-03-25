#ifndef LGSCHARCONST_H
#define LGSCHARCONST_H
#include "LgsConst.h"
#include "types/LgsChar.h"

class LgsCharConst final : public LgsConst {
public:
    char value;

    explicit LgsCharConst(const char value) : LgsConst(new LgsChar()), value(value) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    json asJson() override;
};

#endif //LGSCHARCONST_H
