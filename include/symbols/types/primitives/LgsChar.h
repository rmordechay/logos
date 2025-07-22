#pragma once
#include "LgsType.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
    }
    string prettyName() const override;
    size_t getSizeBytes() override;
    Type* getIRType(LgsModule* module) override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsChar() override = default;
};

inline LgsChar LGS_CHAR;


