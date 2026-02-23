#pragma once
#include "LgsType.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isInt = true;
        isPrimitive = true;
        rttKind = RTT_BOOL;
    }
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    void asIRText(LgsStrBuilder& sb, Value* ptr) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsBool LGS_BOOL;


