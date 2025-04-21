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
    ~LgsIntConst() override = default;
};

#endif //LGSINTCONST_H
