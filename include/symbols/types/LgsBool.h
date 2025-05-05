#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "LgsType.h"
#include "exprs/unary/constants/LgsConstExpr.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    string trueLiteral = "true";

    const string getPrettyName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsBool() override = default;
};

inline LgsBool LGS_BOOL;

#endif // LOGOSBOOL_H
