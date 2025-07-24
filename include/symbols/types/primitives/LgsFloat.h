#pragma once
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isPrimitive = true;
    }
    Type* getIRType(LgsModule* module) override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    string prettyName() override;
    ~LgsFloat() override = default;
};

inline LgsFloat LGS_FLOAT;


