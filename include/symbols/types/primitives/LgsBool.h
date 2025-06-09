#pragma once

#include "exprs/unary/constants/LgsConstExpr.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isPrimitive = true;
        isInt = true;
    }
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsBool() override = default;
};

inline LgsBool LGS_BOOL;


