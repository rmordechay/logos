#pragma once
#include "types/LgsType.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
    }
    string prettyName() const override;
    size_t getSizeBytes() override;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    LgsType* clone() override;
    ~LgsChar() override = default;
};

inline LgsChar LGS_CHAR;


