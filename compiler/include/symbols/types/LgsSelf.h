#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"

class LgsSelf final : public LgsType {
public:
    LgsType* baseType = nullptr;

    explicit LgsSelf() {
        isHeap = true;
        passByRef = true;
        rttKind = RTT_OBJECT;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};
