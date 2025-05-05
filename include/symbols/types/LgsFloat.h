#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    const string getName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsFloat() override = default;
};

inline LgsFloat LGS_FLOAT;

#endif // LOGOSFLOAT_H
