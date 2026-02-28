#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"

class LgsSize final : public LgsType {
public:
    static constexpr auto name = "Size";

    LgsSize() {
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_SIZE;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
};

inline LgsSize LGS_SIZE;