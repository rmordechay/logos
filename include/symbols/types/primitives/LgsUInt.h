#pragma once
#include "LgsType.h"

class LgsUInt final : public LgsType {
public:
    static constexpr auto name = "UInt";

    LgsUInt() {
        isPrimitive = true;
        isInt = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType() override;
    string getIRName() override;
    string pName() const override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsUInt() override = default;
};

inline LgsUInt LGS_UINT;