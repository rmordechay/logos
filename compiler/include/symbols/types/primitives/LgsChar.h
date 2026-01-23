#pragma once
#include "LgsType.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsChar LGS_CHAR;


