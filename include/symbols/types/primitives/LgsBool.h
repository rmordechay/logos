#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H
#include "types/LgsType.h"
#include "exprs/unary/constants/LgsConstExpr.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    string getStrFormatPart() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    ~LgsBool() override = default;
};

inline LgsBool LGS_BOOL;

#endif // LOGOSBOOL_H
