#pragma once
#include "LgsType.h"

class LgsShort final : public LgsType {
public:
    static constexpr auto name = "Short";

    LgsShort() {
        isInt = true;
        rtt = RTT_SHORT;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsShort LGS_SHORT;


