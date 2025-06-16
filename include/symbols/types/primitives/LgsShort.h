#pragma once
#include "LgsType.h"

class LgsShort final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsShort() {
        isPrimitive = true;
        isInt = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsShort() override = default;
};

inline LgsShort LGS_SHORT;


