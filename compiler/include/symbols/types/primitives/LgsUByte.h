#pragma once
#include "LgsType.h"

class LgsUByte final : public LgsType {
public:
    static constexpr auto name = "UByte";

    LgsUByte() {
        isUnsinged = true;
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_UBYTE;
    }
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsUByte LGS_UBYTE;