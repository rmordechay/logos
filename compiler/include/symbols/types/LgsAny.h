#pragma once
#include "LgsType.h"

namespace llvm {
    class DIType;
    class Constant;
    class Type;
}

class LgsAny final : public LgsType {
public:
    static constexpr auto name = "Any";

    size_t sizeBytes() override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

inline LgsAny LGS_ANY;


