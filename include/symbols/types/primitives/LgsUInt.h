#pragma once
#include "LgsType.h"

class LgsUInt final : public LgsType {
public:
    static constexpr auto name = "UInt";

    LgsUInt() {
        isInt = true;
        isUnsigned = true;
        isPrimitive = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsUInt() override = default;
};

inline LgsUInt LGS_UINT;