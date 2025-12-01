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
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsShort LGS_SHORT;


