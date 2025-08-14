#pragma once
#include "LgsType.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
    }
    std::string prettyName() override;
    size_t getSizeBytes() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsChar() override = default;
};

inline LgsChar LGS_CHAR;


