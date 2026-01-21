#pragma once
#include "LgsType.h"
#include "codegen/LgsCgModule.h"

class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isInt = true;
    }
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsLong LGS_LONG;


