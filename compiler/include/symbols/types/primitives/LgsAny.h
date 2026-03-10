#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"

namespace llvm {
    class DIType;
    class Constant;
    class Type;
}

class LgsAny final : public LgsType {
public:
    static constexpr auto name = "Any";

    LgsAny() {
        isPrimitive = true;
        rttKind = RTT_ANY;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsAny LGS_ANY;


