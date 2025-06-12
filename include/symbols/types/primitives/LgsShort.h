#pragma once
#include "types/LgsType.h"

class LgsShort final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsShort() {
        setFlag(PRIMITIVE);
        setFlag(INT);
    }
    size_t getSizeBytes() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    LgsType* clone() override;
    ~LgsShort() override = default;
};

inline LgsShort LGS_SHORT;


