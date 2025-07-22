#pragma once
#include "LgsType.h"
#include "logos/LgsModule.h"

class LgsSize final : public LgsType {
public:
    static constexpr auto name = "Size";

    LgsSize() {
        isPrimitive = true;
        isInt = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsModule* module) override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsSize() override = default;
};

inline LgsSize LGS_SIZE;