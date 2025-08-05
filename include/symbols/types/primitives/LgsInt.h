#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isPrimitive = true;
        isNumber = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsInt() override = default;
};

inline LgsInt LGS_INT;
