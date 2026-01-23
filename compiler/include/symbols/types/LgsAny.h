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
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsAny LGS_ANY;


