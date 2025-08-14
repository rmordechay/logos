#pragma once
#include "LgsType.h"
#include "logos/LgsCodeGen.h"


class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isPrimitive = true;
        isNumber = true;
    }
    Type* getIRType(LgsCodeGen* codeGen) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    std::string getName() override;
    std::string prettyName() override;
    bool equals(LgsType* other) override;
    ~LgsLong() override = default;
};

inline LgsLong LGS_LONG;


