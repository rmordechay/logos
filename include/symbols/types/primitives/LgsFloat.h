#pragma once
#include "types/LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isPrimitive = true;
    }
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    string prettyName() const override;
    ~LgsFloat() override = default;
};

inline LgsFloat LGS_FLOAT;


