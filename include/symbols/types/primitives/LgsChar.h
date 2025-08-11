#pragma once
#include "LgsType.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
    }
    string prettyName() override;
    size_t getSizeBytes() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    string strFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsChar() override = default;
};

inline LgsChar LGS_CHAR;


