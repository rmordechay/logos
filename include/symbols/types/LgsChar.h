#ifndef LGSCHAR_H
#define LGSCHAR_H
#include "LgsBool.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"
#include "exprs/unary/LgsUnaryExpr.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsChar() override = default;
};

#endif //LGSCHAR_H
