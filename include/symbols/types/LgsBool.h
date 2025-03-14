#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LgsType.h"
#include "constants/LgsConstant.h"

class LgsBool final : public LgsType {
public:
    Type* IRType = Type::getInt1Ty(context);
    string typeName = "Bool";
    string trueLiteral = "true";

    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
    ~LgsBool() override = default;
};

inline LgsBool LOGOS_BOOL;

#endif // LOGOSBOOL_H
