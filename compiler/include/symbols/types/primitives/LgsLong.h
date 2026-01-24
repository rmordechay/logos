#pragma once
#include "LgsType.h"
#include "codegen/LgsCodeGen.h"

class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isInt = true;
        rtt = RTT_LONG;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsLong LGS_LONG;


