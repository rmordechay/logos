#pragma once
#include "LgsType.h"

class LgsByte final : public LgsType {
public:
    static constexpr auto name = "Byte";

    LgsByte() {
        isInt = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsByte LGS_BYTE;