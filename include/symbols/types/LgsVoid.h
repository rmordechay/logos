#pragma once
#include "LgsType.h"

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";

    LgsVoid() {
        isVoid = true;
    }
    string prettyName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    size_t getSizeBytes() override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    ~LgsVoid() override = default;
};

inline LgsVoid LGS_VOID;


