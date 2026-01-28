#pragma once
#include "LgsType.h"

class LgsUInt final : public LgsType {
public:
    static constexpr auto name = "UInt";

    LgsUInt() {
        isUnsinged = true;
        isInt = true;
        rttKind = RTT_UINT;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsUInt LGS_UINT;