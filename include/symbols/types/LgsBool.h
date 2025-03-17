#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LgsType.h"
#include "exprs/unary/constants/LgsConst.h"

class LgsBool final : public LgsType {
public:
    string name = "Bool";
    string trueLiteral = "true";
    Type* IRType = Type::getInt1Ty(context);

    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsBool() override = default;
};

inline LgsBool LOGOS_BOOL;

#endif // LOGOSBOOL_H
