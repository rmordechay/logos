#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"

class LgsUInt final : public LgsType {
public:
    static constexpr auto name = "UInt";

    LgsUInt() {
        isUnsinged = true;
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_UINT;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsUInt LGS_UINT;