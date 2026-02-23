#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"

class LgsByte final : public LgsType {
public:
    static constexpr auto name = "Byte";

    LgsByte() {
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_BYTE;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsByte LGS_BYTE;