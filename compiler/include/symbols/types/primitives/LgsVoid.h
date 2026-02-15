#pragma once
#include "LgsType.h"

class LgsVoid final : public LgsType {
public:
    static constexpr auto name = "Void";

    LgsVoid() {
        isPrimitive = true;
        rttKind = RTT_VOID;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsVoid LGS_VOID;


