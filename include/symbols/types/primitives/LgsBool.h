#pragma once
#include "LgsType.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isPrimitive = true;
        isNumber = true;
    }
    string prettyName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    string strFormatPart() const override;
    size_t getSizeBytes() override;
    bool equals(LgsType* other) override;
    ~LgsBool() override = default;
};

inline LgsBool LGS_BOOL;


