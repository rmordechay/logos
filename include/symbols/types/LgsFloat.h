#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LgsType.h"
#include "constants/LgsConstant.h"
#include "funcs/LgsMethodImpl.h"

class LgsFloat final : public LgsType {
public:
    Type* IRType = Type::getFloatTy(context);
    string typeName = "Float";

    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
    ~LgsFloat() override = default;
};

inline LgsFloat LOGOS_FLOAT;

#endif // LOGOSFLOAT_H
