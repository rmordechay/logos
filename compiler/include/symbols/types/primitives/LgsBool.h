#pragma once
#include "LgsType.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isInt = true;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    Value* asIRStr(LgsCodeGen& cg, Value* v) override;
    size_t sizeBytes() override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    LgsType* clone() override;
};

inline LgsBool LGS_BOOL;


