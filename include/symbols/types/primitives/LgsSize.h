#pragma once
#include "LgsType.h"

class LgsSize final : public LgsType {
public:
    static constexpr auto name = "Size";

    LgsSize() {
        isPrimitive = true;
        isNumber = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    string strFormatPart() const override;
    ~LgsSize() override = default;
};

inline LgsSize LGS_SIZE;