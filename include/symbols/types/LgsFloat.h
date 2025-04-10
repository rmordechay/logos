#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LgsType.h"
#include "exprs/unary/constants/LgsConstExpr.h"
#include "funcs/LgsMethodImpl.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    const string getName() const override;
    size_t size() override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsFloat() override = default;
};

inline LgsFloat LOGOS_FLOAT;

#endif // LOGOSFLOAT_H
