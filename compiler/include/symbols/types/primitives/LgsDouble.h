#pragma once
#include "LgsType.h"

class LgsDouble final : public LgsType {
public:
    static constexpr auto name = "Double";
    LgsDouble() {
        isPrimitive = true;
        isFloatingPoint = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    Value* powIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* clone() override;
};

inline LgsDouble LGS_DOUBLE;