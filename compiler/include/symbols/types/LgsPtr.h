#pragma once
#include "LgsType.h"

class LgsPtr final : public LgsType {
public:
    static constexpr auto name = "Ptr";
    LgsType* baseType;

    explicit LgsPtr(LgsType* baseType) : baseType(baseType) {}
    std::string getName() override;
    std::string pname() override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsPtr() override;
};
