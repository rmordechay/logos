#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"

class LgsShort final : public LgsType {
public:
    static constexpr auto name = "Short";

    LgsShort() {
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_SHORT;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsShort LGS_SHORT;


