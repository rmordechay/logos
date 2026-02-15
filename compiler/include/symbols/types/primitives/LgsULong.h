#pragma once
#include "LgsType.h"

class LgsULong final : public LgsType {
public:
    static constexpr auto name = "ULong";

    LgsULong() {
        isUnsinged = true;
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_ULONG;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsULong LGS_ULONG;