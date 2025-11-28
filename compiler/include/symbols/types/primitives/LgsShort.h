#pragma once
#include "LgsType.h"

class LgsShort final : public LgsType {
public:
    static constexpr auto name = "Short";

    LgsShort() {
        isPrimitive = true;
        isInt = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* clone() override;
};

inline LgsShort LGS_SHORT;


