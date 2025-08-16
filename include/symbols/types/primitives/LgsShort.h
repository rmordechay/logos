#pragma once
#include "LgsType.h"

class LgsShort final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsShort() {
        isPrimitive = true;
        isNumber = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
    ~LgsShort() override = default;
};

inline LgsShort LGS_SHORT;


