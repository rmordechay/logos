#pragma once
#include "LgsType.h"

class LgsUShort final : public LgsType {
public:
    static constexpr auto name = "UShort";
    LgsUShort() {
        isUnsinged = true;
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_USHORT;
    }
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Type* getIRType(LgsCodeGen& cg) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsUShort LGS_USHORT;