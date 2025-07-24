#pragma once
#include "LgsType.h"
#include "logos/LgsModule.h"


class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isPrimitive = true;
        isInt = true;
    }
    Type* getIRType(LgsModule* module) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    string getName() override;
    string prettyName() override;
    bool equals(LgsType* other) override;
    ~LgsLong() override = default;
};

inline LgsLong LGS_LONG;


