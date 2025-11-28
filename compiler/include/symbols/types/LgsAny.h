#pragma once
#include "LgsType.h"

class LgsAny final : public LgsType {
public:
    static constexpr auto name = "Any";

    LgsAny() {
        isPrimitive = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsAny LGS_ANY;


