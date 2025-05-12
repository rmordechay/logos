#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "types/LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    string prettyName() const override;
    ~LgsFloat() override = default;
};

inline LgsFloat LGS_FLOAT;

#endif // LOGOSFLOAT_H
