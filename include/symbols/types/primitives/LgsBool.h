#ifndef LOGOSBOOL_H
#define LOGOSBOOL_H

#include "exprs/unary/constants/LgsConstExpr.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isPrimitive = true;
    }
    string prettyName() const override;
    llvm::Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsBool() override = default;
};

inline LgsBool LGS_BOOL;

#endif // LOGOSBOOL_H
