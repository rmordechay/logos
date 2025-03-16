#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LgsType.h"
#include "constants/LgsConst.h"
#include "funcs/LgsMethodImpl.h"

class LgsFloat final : public LgsType {
public:
    string name = "Float";
    Type* IRType = Type::getFloatTy(context);

    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsFloat() override = default;
};

inline LgsFloat LOGOS_FLOAT;

#endif // LOGOSFLOAT_H
