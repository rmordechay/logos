#pragma once
#include <string>

#include "LgsType.h"
#include "Lgs_Types.h"
#include "codegen/LgsCodeGen.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    LgsChar() {
        isPrimitive = true;
        rttKind = RTT_CHAR;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

inline LgsChar LGS_CHAR;


